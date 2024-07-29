
#include "Grape.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class ExampleLayer : public Grape::ILayer
{
public:
	ExampleLayer()
		: ILayer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Grape::IInput::IsKeyPressed(GP_KEY_TAB))
			GP_INFO("Tab key is pressed (poll).");
	}

	void OnEvent(Grape::IEvent& event) override
	{
		if (event.GetEventType() == Grape::EventType::KeyPressed)
		{
			Grape::KeyPressedEvent& e = (Grape::KeyPressedEvent&)event;
			if (e.GetKeyCode() == GP_KEY_SPACE)
				GP_TRACE("Space key is pressed (event)!");
			GP_TRACE("{0}", (char)e.GetKeyCode());
		}
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

