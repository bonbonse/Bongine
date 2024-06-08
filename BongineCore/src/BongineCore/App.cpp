#include "BongineCore/App.hpp"
#include <iostream>
#include "BongineCore/Log.hpp"
#include "BongineCore/Window.hpp"
#include "BongineCore/Event.hpp"

namespace Bongine {
	
	App::App()
	{
        LOG_INFO("Starting App");
	}

	App::~App()
	{
		LOG_INFO("Closing App");
	}

    int App::start(unsigned int window_width, unsigned int window_height, const char* title)
    {
        m_pWindow = std::make_unique<Window>(title, window_width, window_height);

        m_event_dispatcher.add_event_listener<EventMouseMoved>(
            [](EventMouseMoved& event)
            {
                LOG_INFO("[MouseMoved] Mouse moved to {0}x{1}", event.x, event.y);
            });

        m_event_dispatcher.add_event_listener<EventWindowResize>(
            [](EventWindowResize& event)
            {
                LOG_INFO("[Resized] Changed size to {0}x{1}", event.height, event.height);
            });

        m_event_dispatcher.add_event_listener<EventWindowClose>(
            [&](EventWindowClose& event)
            {
                LOG_INFO("[WindowClose]");
                m_CloseWindow = true;
            });

        m_pWindow->set_event_callback(
            [&](BaseEvent& event)
            {
                m_event_dispatcher.dispatch(event);
            }
        );

        while (!m_CloseWindow)
        {
            m_pWindow->update();
            update();
        }
        m_pWindow = nullptr;

        return 0;
    }
    

}