#include "Window.h"

namespace AC {
    Window::Window(const char* title)
    {

        if (!glfwInit())
            AC_CORE_ERROR("Failed to initalize GLFW!");

        window = glfwCreateWindow(1280, 720, title, NULL, NULL);


        glfwMakeContextCurrent(window);
        if (!window)
        {
            glfwTerminate();
        }

        proc = (GLADloadproc)glfwGetProcAddress;

        if (!gladLoadGLLoader(GetProc())) {
            return;
        }
    }

    void Window::SwapBuffers()
    {

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    void Window::Clear(int mask)
    {
        glClear(mask);
    }

    bool Window::isRunning()
    {
        return !glfwWindowShouldClose(window);
    }

    GLADloadproc& Window::GetProc()
    {
        return proc;
    }
}
