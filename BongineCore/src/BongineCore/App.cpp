#include "BongineCore/App.hpp";
#include <GLFW/glfw3.h>
#include <iostream>
#include "BongineCore/Log.hpp";


namespace Bongine {
	
	App::App()
	{
        LOG_INFO("Welcome");
        LOG_ERROR("Some error message with arg: {}", 1);
        LOG_WARN("Easy padding in numbers like {:08d}", 12);
        LOG_CRITICAL("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
        LOG_INFO("Support for floats {:03.2f}", 1.23456);
        LOG_INFO("Positional args are {1} {0}..", "too", "supported");
        LOG_INFO("{:<30}", "left aligned");
	}

	App::~App()
	{
	}

	int App::start(unsigned int window_width, unsigned int window_height, const char* title) {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            update();
        }

        glfwTerminate();
        return 0;
	}

}