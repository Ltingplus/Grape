#include "Sandbox2D.h"
#include "Grape/Renderer/Renderer.h"

#include "imgui/imgui.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Grape/Renderer/Renderer2D.h"

Sandbox2D::Sandbox2D()
    : ILayer("Sandbox2D")
    , m_cameraController(1280.0f / 720.0f)
{
    m_checkerboardTexture = Grape::ITexture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Grape::Timestep ts)
{
    // Update
    m_cameraController.OnUpdate(ts);

    // Render
    Grape::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Grape::RenderCommand::Clear();

    Grape::Renderer2D::BeginScene(m_cameraController.GetCamera());
    Grape::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Grape::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Grape::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_checkerboardTexture);
    Grape::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_squareColor));
    ImGui::End();
}

void Sandbox2D::OnEvent(Grape::IEvent& e)
{
    m_cameraController.OnEvent(e);
}