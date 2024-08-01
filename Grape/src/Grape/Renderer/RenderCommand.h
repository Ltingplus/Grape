#pragma once

#include "RendererApi.h"


namespace Grape
{
    class RenderCommand
    {
    public:
        static void Clear()
        {
            s_rendererAPI->Clear();
        }
        static void SetClearColor(const glm::vec4& color)
        {
            s_rendererAPI->SetClearColor(color);
        }
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_rendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static RendererAPI* s_rendererAPI;
    };


}