#include <Archimedes.h>

class Sandbox : public AC::Application{
public:
    unsigned int VBO, VAO, EBO, TBO;
    AC::Shader shader;
    AC::Texture tex;
	virtual void Run() override{
        shader = AC::Shader("res/vs.glsl", "res/fs.glsl");
        tex = AC::Texture("res/container.jpg");
        float vertices[] = {
             0.5f,  0.5f, 0.0f, 
             0.5f, -0.5f, 0.0f, 
            -0.5f, -0.5f, 0.0f, 
            -0.5f,  0.5f, 0.0f  
        };
        float texCoords[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
        };
        unsigned int indices[] = {  
            0, 1, 3,   
            1, 2, 3    
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenBuffers(1, &TBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);


        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
	}
    virtual void Render() override {
        shader.Use();
        shader.setInt("tex", tex.getID());
        tex.Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    Sandbox() {

    }
};

AC::Application* AC::CreateApplication() {
	return new Sandbox();
}