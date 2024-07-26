#pragma once

#ifdef GP_PLATFORM_WINDOWS

#include "Log.h"

extern Grape::IApplication* Grape::CreateApplication();

int main(int argc, char** argv)
{
	Grape::Log::Init();
	GP_CORE_WARN("Initialized Log!");
	GP_CLIENT_INFO("Hello!");

	auto app = Grape::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // GP_PLATFORM_WINDOWS
