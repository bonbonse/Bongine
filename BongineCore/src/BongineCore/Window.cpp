#include "BongineCore/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BongineCore/Log.hpp"
#include "Rendering/OpenGL/VertexBuffer.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include "Rendering/OpenGL/ShaderProgram.hpp"

namespace Bongine {

	static bool s_GLFW_initialized = false;

	//Triangle
	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	GLfloat colors[] = {
		1.0f, 0.5f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 1.0f
	};

	const char* vertex_shader =
		"#version 460\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 0) in vec3 vertex_color;"
		"out vec3 color;"
		"void main(){"
		"color = vertex_color;"
		"gl_Position =vec4(vertex_position, 1.0);"
		"}";
	const char* fragment_shader = 
		"#version 460\n"
		"in vec3 color;"
		"out vec4 frag_color;"
		"void main(){"
		"frag_color = vec4(color, 1.0);"
		"}";


	GLuint shader_program;
	GLuint vao;

	std::unique_ptr<ShaderProgram> p_shader_program;
	std::unique_ptr<VertexBuffer> p_points_vbo;
	std::unique_ptr<VertexBuffer> p_colors_vbo;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		: m_data({ title, width, height })
	{
		int resultCode = init();
	}
	Window::~Window() {
		shutdown();
	}
	void Window::shutdown() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	int Window::init() {
		LOG_INFO("Creating window {0} width size {1}x{2}", m_data.title, m_data.width, m_data.height);

		if (!s_GLFW_initialized) {
			if (!glfwInit()) {
				LOG_CRITICAL("Can`t initialize GLMW");
				return -1;
			}
			s_GLFW_initialized = true;
		}

		window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		if (!window)
		{
			LOG_CRITICAL("Can`t create window {0}", m_data.title);

			shutdown();
			return -2;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // принимает строку функции - возвращает адресс
			LOG_CRITICAL("Failde to initialize GLAD");
			return -3;
		}

		glfwSetWindowUserPointer(window, &m_data);
		//Иногда работает, иногда нет. functional проблема, видимо из-за обращение в память, которая не успела измениться или наоброт
		glfwSetWindowSizeCallback(window, 
			[](GLFWwindow* window, int width, int height) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.width = width;
				data.height = height;

				EventWindowResize event(width, height);
				data.eventCallbackFn(event);
			}
			);
		glfwSetCursorPosCallback(window, 
			[](GLFWwindow* window, double x, double y) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				EventMouseMoved event(x, y);
				data.eventCallbackFn(event);
			}
			);
		glfwSetWindowCloseCallback(window,
			[](GLFWwindow* window) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				EventWindowClose event;
				data.eventCallbackFn(event);
			});
		glfwSetFramebufferSizeCallback(window,
			[](GLFWwindow* window, int width, int height) {
				glViewport(0, 0, width, height);
			});
		


		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, &vertex_shader, nullptr);
		glCompileShader(vs);

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, &fragment_shader, nullptr);
		glCompileShader(fs);

		shader_program = glCreateProgram();
		glAttachShader(shader_program, vs);
		glAttachShader(shader_program, fs);
		glLinkProgram(shader_program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
		if (!p_shader_program->isCompiled())
		{
			return false;
		}

		p_points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points));
		p_colors_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors));

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		p_points_vbo->bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		p_colors_vbo->bind();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		update();

		return 0;

	}


	void Window::update() {
		glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		p_shader_program->bind();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize.x = static_cast<float>(getWidth());
		io.DisplaySize.y = static_cast<float>(getHeight());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Begin("Backgr");
		ImGui::ColorEdit4("Back", m_background_color);
		ImGui::End();

		ImGui::Begin("Lira");
		ImGui::ColorEdit4("Back", m_background_color);
		ImGui::End();



		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}