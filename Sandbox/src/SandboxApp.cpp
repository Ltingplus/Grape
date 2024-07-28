
#include "Grape.h"

class ExampleLayer : public Grape::ILayer
{
public:
	ExampleLayer()
		: ILayer("Example")
	{
	}

	void OnUpdate() override
	{
		GP_INFO("ExampleLayer::Update");
	}

	void OnEvent(Grape::IEvent& event) override
	{
		GP_TRACE("{0}", event.ToString());
	}
};
class SandboxApp : public Grape::IApplication
{
public:
	SandboxApp()
	{
		PushLayer(new ExampleLayer());
		PushOverlayer(new Grape::ImGuiLayer());
	}

	~SandboxApp()
	{

	}

};

Grape::IApplication* Grape::CreateApplication()
{
	return new SandboxApp();
}

