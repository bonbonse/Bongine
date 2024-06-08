#pragma once

#include "BongineCore/Event.hpp"

#include <string>
#include <functional>

struct GLFWwindow;

namespace Bongine {

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(BaseEvent&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		int getWidth() { return m_data.width; }
		int getHeight() { return m_data.height; }
		std::string getTitle() { return m_data.title; }
		void Window::update();

		void set_event_callback(const EventCallbackFn callback) {
			m_data.eventCallbackFn = callback;
		}


	private:
		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			EventCallbackFn eventCallbackFn;
		};

		GLFWwindow* window = nullptr;
		WindowData m_data;

		int init();
		void shutdown();
	};
}