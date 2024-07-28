

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Log.h"

#include <GLFW/glfw3.h>

namespace Grape
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	IApplication::IApplication()
		: m_window(IWindow::Create())
	{
		m_window->SetEventCallback(BIND_EVENT_FN(IApplication::OnEvent));
	}

	IApplication::~IApplication()
	{
	}

	void IApplication::Run()
	{
		while (m_running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto layer : m_layerStack)
				layer->OnUpdate();

			m_window->OnUpdate();
		}
	}

	void IApplication::OnEvent(IEvent& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(IApplication::OnWindowClose));

		//GP_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.IsHandled())
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

}