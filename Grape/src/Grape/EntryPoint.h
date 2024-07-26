#pragma once

#ifdef GP_PLATFORM_WINDOWS

extern Grape::IApplication* Grape::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Grape::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // GP_PLATFORM_WINDOWS
