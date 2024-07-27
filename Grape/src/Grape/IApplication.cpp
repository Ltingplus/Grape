

#include "gppch.h"
#include "IApplication.h"

#include "Grape/Events/ApplicationEvent.h"
#include "Grape/Log.h"

namespace Grape
{
	IApplication::IApplication()
	{

	}

	IApplication::~IApplication()
	{

	}

	void IApplication::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
			GP_CLIENT_INFO("Hello!");
		if (e.IsInCategory(EventCategoryInput))
			;//GP_CLIENT_TRACE(e);

		while (true);
	}

}