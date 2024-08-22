

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Core/Log.h"

#include "glad/glad.h"
#include "Grape/Utils/Timestep.h"
#include "GLFW/glfw3.h"
#include "Grape/Renderer/Renderer.h"

namespace Grape
{

    IApplication* IApplication::s_instance = nullptr;

    IApplication::IApplication()
        : m_window(IWindow::Create())
    {
        GP_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;
        m_window->SetEventCallback(GP_BIND_EVENT_FN(IApplication::OnEvent));

        Renderer::Init();

        m_imGuiLayer = new ImGuiLayer();
        PushOverlayer(m_imGuiLayer);
    }

    IApplication::~IApplication()
    {
    }

    void IApplication::Run()
    {
        while (m_running)
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_lastFrameTime;
            m_lastFrameTime = time;
            if (!m_minimized)
            {
                for (auto layer : m_layerStack)
                    layer->OnUpdate(timestep);
            }

            m_imGuiLayer->Begin();
            for (auto layer : m_layerStack)
                layer->OnImGuiRender();
            m_imGuiLayer->End();

            m_window->OnUpdate();
        }

    }

    void IApplication::OnEvent(IEvent& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(GP_BIND_EVENT_FN(IApplication::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(GP_BIND_EVENT_FN(IApplication::OnWindowResize));

        //GP_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
    }

    void IApplication::PushLayer(ILayer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

    void IApplication::PushOverlayer(ILayer* layer)
    {
        m_layerStack.PushOverlayer(layer);
    }

    bool IApplication::OnWindowClose(WindowCloseEvent& e)
    {
        m_running = false;
        return true;
    }

    bool IApplication::OnWindowResize(WindowResizeEvent& e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_minimized = true;
            return false;
        }
        m_minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return false;
    }

}