#include <Archimedes.h>

class Sandbox : public AC::Application{
AC::Camera cam = AC::Camera(-1.6f, 1.6f, -0.9f, 0.9f);
public:
    AC::Sprite s = AC::Sprite(AC::Texture("res/container.jpg"));
	virtual void Run() override{
	}
    virtual void Render() override {
        s.Render(cam);
    }
    Sandbox() {

    }
};

AC::Application* AC::CreateApplication() {
	return new Sandbox();
}