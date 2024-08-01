#include "gppch.h"
#include "Renderer.h"

namespace Grape
{

    void Renderer::BeginScene()
    {
        // todo
    }

    void Renderer::EndScene()
    {
        //todo
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}