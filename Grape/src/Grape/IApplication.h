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

		void Run();
		void OnEvent(IEvent& e);

		void PushLayer(ILayer* layer);
		void PushOverlayer(ILayer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:

	private:
		std::unique_ptr<IWindow> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	IApplication* CreateApplication();

}

