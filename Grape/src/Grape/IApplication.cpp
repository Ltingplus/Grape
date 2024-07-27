

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Log.h"

#include <GLFW/glfw3.h>

namespace Grape
{
	IApplication::IApplication()
	{
		m_window = IWindow::Create();
		//m_window = std::make_unique<IWindow>(IWindow::Create());
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
			m_window->OnUpdate();
		}
	}

}