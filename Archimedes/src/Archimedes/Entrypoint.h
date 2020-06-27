#pragma once
#include "Application.h"
#include "Log.h"
#include "Window.h"

namespace AC {
	extern AC::Application* CreateApplication();
}

int main(){
	AC::Log::Init();
	AC_CORE_INFO("Initialized Log!");

	AC::Window win = AC::Window();

	if (!gladLoadGLLoader(win.GetProc())) {
		AC_CORE_ERROR("Failed to initalize Glad!");
	}


	auto app = AC::CreateApplication();

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	app->Run();

	while (win.isRunning()) {
		glClearColor(1, 0, 0, 1);
		win.Clear();
		app->Render();
		win.SwapBuffers();
	}
}