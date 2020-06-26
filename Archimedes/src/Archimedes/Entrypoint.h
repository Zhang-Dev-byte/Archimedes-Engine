#pragma once
#include "Application.h"
#include "Log.h"

namespace AC {
	extern AC::Application* CreateApplication();
}

int main(){
	AC::Log::Init();
	AC_CORE_INFO("Initialized Log!");
	auto app = AC::CreateApplication();
	app->Run();
	while (true);
}