#pragma once

#include "Core.h"
#include "Events/IEvent.h"

namespace Grape
{
	class GRAPE_API IApplication
	{
	public:
		IApplication();
		virtual ~IApplication();

		void Run();
	};

	IApplication* CreateApplication();

}

