#include "Window.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Sprite.h"

namespace AC {
    Window::Window(const char* title)
    {

        if (!glfwInit())
            AC_CORE_ERROR("Failed to initalize GLFW!");

        window = glfwCreateWindow(1280, 720, title, NULL, NULL);


        glfwMakeContextCurrent(window);
        if (!window)
        {
            glfwTerminate();
        }

        proc = (GLADloadproc)glfwGetProcAddress;

        if (!gladLoadGLLoader(GetProc())) {
            return;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImFont* pFont = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 16);
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(NULL);
    }

    void Window::SwapBuffers()
    {

        static bool p_open = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", &p_open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        ImGui::Begin("Viewport");
        ImGui::Image((void*)(intptr_t)(TCB), ImVec2(960/1.3f, 540/1.3f));
        ImGui::End();
        ImGui::Begin("Scene");
        for (auto i = sprites.begin(); i != sprites.end(); i++) {
            Sprite* p = *i;
            Sprite& r = *p;

            if (ImGui::Button(r.GetName(), ImVec2(100, 20))) {
                ssprite = p;
            }
        }
        ImGui::End();
        ImGui::Begin("Properties");
        Sprite& r = *ssprite;

        spos[0] = r.GetPosition().x;
        spos[1] = r.GetPosition().y;

        sscale[0] = r.GetScale().x;
        sscale[1] = r.GetScale().y;

        srot = r.GetRotation();

        ImGui::Text(r.GetName());
        ImGui::InputFloat2("Position", spos);
        ImGui::InputFloat2("Scale", sscale);
        ImGui::InputFloat("Rotation", &srot);

        r.SetPosition(vec2(spos[0], spos[1]));
        r.SetScale(vec2(sscale[0], sscale[1]));

        r.SetRotation(srot);
        ImGui::End();
        ImGui::Begin("Control");
        ImGui::End();
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void Window::Clear(int mask)
    {
        glClear(mask);


        ImGui_ImplOpenGL3_NewFrame();

        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    bool Window::isRunning()
    {
        return !glfwWindowShouldClose(window);
    }

    void Window::SetTCB(unsigned int value)
    {
        TCB = value;
    }

    void Window::SetSprites(vector<Sprite*>& value)
    {
        sprites = value;
    }

    vector<Sprite*>& Window::GetSprites()
    {
        return sprites;
    }

    GLFWwindow** Window::GetWindow()
    {
        return &window;
    }

    GLADloadproc& Window::GetProc()
    {
        return proc;
    }
}
