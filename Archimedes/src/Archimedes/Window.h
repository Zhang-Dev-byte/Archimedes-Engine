#pragma once
#include "Core.h"
#include "Log.h"
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Texture.h"
#include "Sprite.h"
#include <vector>

using std::vector;
namespace AC {
	class AC_API Window {
	public:
		Window(const char* title = "Archimedes Engine");
		void SwapBuffers();
		void Clear(int mask = GL_COLOR_BUFFER_BIT);
		bool isRunning();
		void SetTCB(unsigned int value);
		void SetSprites(vector<Sprite*>& value);
		GLFWwindow** GetWindow();
		GLADloadproc& GetProc();
	private:
		GLFWwindow* window;
		GLADloadproc proc;
		unsigned int TCB;
		vector<Sprite*> sprites;
	};
}