
#include "Grape.h"

class SandboxApp : public Grape::IApplication
{
public:
	SandboxApp()
	{

	}

	~SandboxApp()
	{

	}

};

Grape::IApplication* Grape::CreateApplication()
{
	return new SandboxApp();
}

