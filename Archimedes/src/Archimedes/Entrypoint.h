#pragma once
#include "Application.h"
#include "Log.h"
#include "Window.h"
#include "Editor.h"
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

namespace AC {
	extern Application* CreateApplication();
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
	win.SetTCB(TCB);
	win.SetSprites(sprites);
	bool show = true;
	while (win.isRunning()) {
		glClearColor(1, 0, 0, 1);
		win.Clear();
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto i = sprites.begin(); i != sprites.end(); ++i) {
			AC::Sprite* p = *i;
			AC::Sprite& r = *p;

			r.Render(ecam);
		}

		app->Render();

		win.SwapBuffers();
	}
}