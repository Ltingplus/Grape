#pragma once

#include "Core.h"

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

