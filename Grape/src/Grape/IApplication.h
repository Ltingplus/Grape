#pragma once

#include "Core.h"
#include "Events/IEvent.h"
#include "Events/ApplicationEvent.h"
#include "IWindow.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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

        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<Shader> m_blueShader;
        std::shared_ptr<VertexArray> m_squareVertexArray;
    };

    IApplication* CreateApplication();

}

