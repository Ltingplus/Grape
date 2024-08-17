#pragma once

#include "RendererApi.h"


namespace Grape
{
    class RenderCommand
    {
    public:
        static void Init()
        {
            s_rendererAPI->Init();
        }
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
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t hight)
        {
            s_rendererAPI->SetViewport(x, y, width, hight);
        }

    private:
        static RendererAPI* s_rendererAPI;
    };


}