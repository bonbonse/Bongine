#include "BongineCore/Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "BongineCore/Log.hpp"

namespace Bongine {

	static bool s_GLFW_initialized = false;

	Window::Window(std::string title, const unsigned int width, const unsigned int height)
		:title(std::move(title))
		, width(width)
		, height(height)
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
		LOG_INFO("Creating window {0} width size {1}x{2}", title, width, height);

		if (!s_GLFW_initialized) {
			if (!glfwInit()) {
				LOG_CRITICAL("Can`t initialize GLMW");
				return -1;
			}
			s_GLFW_initialized = true;
		}

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window)
		{
			LOG_CRITICAL("Can`t create window {0}", title);

			shutdown();
			return -2;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // принимает строку функции - возвращает адресс
			LOG_CRITICAL("Failde to initialize GLAD");
			return -3;
		}

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