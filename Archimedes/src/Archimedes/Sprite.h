#pragma once
#include "Core.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"
#include "Camera.h"

namespace AC {
    class AC_API Sprite {
    public:
        Sprite(Texture& texture, const char* name);
        void Render(Camera& cam);
        void UpdateModel();
        void SetScale(vec2& value);
        void SetPosition(vec2& value);
        void SetRotation(float value);

        vec2& GetScale();
        vec2& GetPosition();
        float GetRotation();

        const char* GetName();

        void Scale(vec2& value);
        void Translate(vec2& value);
        void Rotate(float value);
    private:
        unsigned int VBO, VAO, EBO, TBO;
        AC::Shader shader;
        AC::Texture tex;
        mat4 model;
        vec2 position;
        vec2 scale;
        float rotation;
        const char* name;
    };
}