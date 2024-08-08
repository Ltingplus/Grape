#include "gppch.h"
#include "Renderer.h"

namespace Grape
{
    Renderer::SceneData* Renderer::s_sceneData = new Renderer::SceneData;

    void Renderer::BeginScene(const OrthographicCamera& carema)
    {
        s_sceneData->ViewProjectionMatrix = carema.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {
        //todo
    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UpdateUniformMatrix("u_viewProjection", s_sceneData->ViewProjectionMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}