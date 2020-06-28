#include <Archimedes.h>

class Sandbox2D : public AC::Application{
AC::Camera cam = AC::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
public:
    AC::Sprite s = AC::Sprite(AC::Texture("res/container.jpg"));
    AC::Shader sh = AC::Shader("res/svs.glsl", "res/sfs.glsl");

    unsigned int quadVAO, quadVBO, FBO, TCB, RBO;

    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
	virtual void Run() override{
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        glGenTextures(1, &TCB);
        glBindTexture(GL_TEXTURE_2D, TCB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TCB, 0);


        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            AC_CORE_ERROR("Framebuffer not complete!");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	}
    virtual void Render() override {
        s.Render(cam);
        //glBindTexture(GL_TEXTURE_2D, TCB);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClear(GL_COLOR_BUFFER_BIT);
        s.Render(cam);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        sh.Use();
        sh.setInt("screenTexture", 0);
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    Sandbox2D() {

    }
};


AC::Application* AC::CreateApplication() {
    return new Sandbox2D();
}