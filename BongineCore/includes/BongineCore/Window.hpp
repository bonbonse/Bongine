#pragma once

#include <string>

struct GLFWwindow;

namespace Bongine {

	class Window
	{
	public:
		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		int getWidth() { return width; }
		int getHeight() { return height; }
		std::string getTitle() { return title; }
		void Window::update();

	private:
		int init();
		void shutdown();

		GLFWwindow* window;
		int width;
		int height;
		std::string title;

	};
}