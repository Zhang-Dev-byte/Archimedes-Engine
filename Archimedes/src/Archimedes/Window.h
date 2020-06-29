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
		void Setecam(Camera& value);
		void Setgcam(Camera& value);
		Camera& Getecam();
		Camera& Getgcam();
		vector<Sprite*>& GetSprites();
		GLFWwindow** GetWindow();
		GLADloadproc& GetProc();
	private:
		GLFWwindow* window;
		GLADloadproc proc;
		unsigned int TCB;
		Sprite* ssprite = new Sprite();
		vector<Sprite*> sprites;
		Camera gcam;
		Camera ecam;
		float spos[2] = {0,0};
		float sscale[2] = {0,0};
		float srot = 0;
	};
}