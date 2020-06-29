#include <Archimedes.h>
#include "Archimedes/nlohmann/json.hpp"

using namespace nlohmann;

class Sandbox2D : public AC::Application{
public:
    AC::Sprite s = AC::Sprite(AC::Texture("res/container.jpg"), "Hello");
    AC::Sprite se = AC::Sprite(AC::Texture("res/container.jpg"), "Hellok");
    AC::Sprite sek = AC::Sprite(AC::Texture("res/container.jpg"), "Hellog");
    AC::Sprite sekg = AC::Sprite(AC::Texture("res/container.jpg"), "Hellogk");

	virtual void Run() override{
        sek.SetPosition(vec2( 0.5f,0.5f ));
        se.SetPosition(vec2( -0.5f,-0.5f ));
        sekg.SetRotation(45);
        AC::AddSprite(&s);
        AC::AddSprite(&se);
        AC::AddSprite(&sek);
        AC::AddSprite(&sekg);

        json j;
        j["X"] = s.GetPosition().x;
        j["Y"] = s.GetPosition().y;

        j["SX"] = s.GetScale().x;
        j["SY"] = s.GetScale().y;

        j["R"] = s.GetRotation();

        j["N"] = s.GetName();

        AC_CORE_INFO(j.dump());
        AC::CreateFrameBuffer();

        sekg.SetPosition(vec2(2.0f, 2.0f));
        s.SetPosition(vec2(2.0f, 2.0f));

	}
    virtual void Update() override {

    }
    Sandbox2D() {

    }
};


AC::Application* AC::CreateApplication() {
    return new Sandbox2D();
}