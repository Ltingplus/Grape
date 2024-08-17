#include "gppch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Grape
{
    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::Init()
    {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const OrthographicCamera& carema)
    {
        s_sceneData->ViewProjectionMatrix = carema.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
        //todo
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::Submit(const std::shared_ptr<IShader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UpdateUniformMatrix4("u_viewProjection", s_sceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UpdateUniformMatrix4("u_transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}