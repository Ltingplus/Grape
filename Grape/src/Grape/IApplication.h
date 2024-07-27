#pragma once

#include "Core.h"
#include "Events/IEvent.h"
#include "IWindow.h"

namespace Grape
{
	class GRAPE_API IApplication
	{
	public:
		IApplication();
		virtual ~IApplication();

		void Run();

	private:
		//std::unique_ptr<IWindow> m_window;
		IWindow* m_window;
		bool m_running = true;
	};

	IApplication* CreateApplication();

}

