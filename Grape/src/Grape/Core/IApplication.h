#pragma once

#include "Core.h"
#include "Grape/Events/IEvent.h"
#include "Grape/Events/ApplicationEvent.h"
#include "IWindow.h"
#include "LayerStack.h"
#include "Grape/ImGui/ImGuiLayer.h"

namespace Grape
{
    class GRAPE_API IApplication
    {

    public:
        IApplication();
        virtual ~IApplication();

        static IApplication& Get() { return *s_instance; }

        void Run();
        void OnEvent(IEvent& e);

        void PushLayer(ILayer* layer);
        void PushOverlayer(ILayer* layer);

        IWindow& GetWindow() { return *m_window; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

    private:
        static IApplication* s_instance;

    private:
        std::unique_ptr<IWindow> m_window;
        bool m_running = true;
        bool m_minimized = false;
        LayerStack m_layerStack;

        float m_lastFrameTime = 0.0f;
        ImGuiLayer* m_imGuiLayer;
    };

    IApplication* CreateApplication();

}

