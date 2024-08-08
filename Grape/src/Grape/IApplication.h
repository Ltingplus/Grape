#pragma once

#include "Core.h"
#include "Events/IEvent.h"
#include "Events/ApplicationEvent.h"
#include "IWindow.h"
#include "LayerStack.h"

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

    private:
        static IApplication* s_instance;

    private:
        std::unique_ptr<IWindow> m_window;
        bool m_running = true;
        LayerStack m_layerStack;

        float m_lastFrameTime = 0.0f;
    };

    IApplication* CreateApplication();

}

