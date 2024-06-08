#include "BongineCore/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BongineCore/Log.hpp"

namespace Bongine {

	static bool s_GLFW_initialized = false;

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

		update();

		return 0;

	}

	void Window::update() {
		glClearColor(1, 0, 0, 0);

		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}