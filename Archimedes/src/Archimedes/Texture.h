#pragma once
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include "Core.h"

namespace AC {
	class AC_API Texture {
	private:
		int width, height;
		int comp;
		unsigned int id;

	public:
		Texture(const char* path);
		Texture();
		void Bind();
		void UnBind();
		unsigned int getID();
		int getWidth();
		int getHeight();
	};
}