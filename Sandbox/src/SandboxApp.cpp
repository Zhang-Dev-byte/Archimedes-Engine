#include <Archimedes.h>

class Sandbox : public AC::Application{
public:
	virtual void Run() override{

	}
};

AC::Application* AC::CreateApplication() {
	return new Sandbox();
}