#pragma once
#include "Core.h"
#include "Log.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace AC {
	class AC_API Window {
	public:
		Window(const char* title = "Archimedes Engine");
		void SwapBuffers();
		void Clear(int mask = GL_COLOR_BUFFER_BIT);
		bool isRunning();
		GLADloadproc& GetProc();
	private:
		GLFWwindow* window;
		GLADloadproc proc;
	};
}