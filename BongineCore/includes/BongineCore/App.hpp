#pragma once

namespace Bongine {

#pragma comment (lib, "opengl32.lib")

	class App
	{
	public:
		App();
		virtual ~App();
		App(const App&) = delete;
		App(App&&) = delete;
		App& operator=(const App&) = delete;
		App& operator=(App&&) = delete;

		virtual int start(unsigned int window_width, unsigned int window_height, const char* title);

		virtual void update() {}
	private:

	};

	

}