#pragma once
#include "Application.h"

namespace AC {
	extern AC::Application* CreateApplication();
}

int main(){
	auto app = AC::CreateApplication();
	app->Run();
	while (true);
}