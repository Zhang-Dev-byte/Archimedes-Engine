#pragma once
#include "Core.h"

namespace AC {
	class AC_API Application {
	public:
		Application();
		virtual void Run() = 0;
	};
}