#pragma once

#include "Core.h"
#include "Events/IEvent.h"
#include "Events/ApplicationEvent.h"
#include "IWindow.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

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

        unsigned int m_vertexArray;
        std::unique_ptr<Shader> m_shader;
        std::unique_ptr<VertexBuffer> m_vertexBuffer;
        std::unique_ptr<IndexBuffer> m_indexBuffer;
    };

    IApplication* CreateApplication();

}

