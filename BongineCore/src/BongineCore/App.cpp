#include "BongineCore/App.hpp"
#include <iostream>
#include "BongineCore/Log.hpp"
#include "BongineCore/Window.hpp"



namespace Bongine {
	
	App::App()
	{
        LOG_INFO("Starting App");
	}

	App::~App()
	{
		LOG_INFO("Closing App");
	}

	int App::start(unsigned int window_width, unsigned int window_height, const char* title) {
		m_pWindow = std::make_unique<Window>(title, window_width, window_height);

		while (true) {
			m_pWindow->update();
			update();
		}
       
		return 0;
	}
    

}