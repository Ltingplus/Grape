#pragma once
#include "RenderCommand.h"

namespace Grape
{    

    class Renderer
    {
    public:
        static RendererAPI::Api GetAPI() { return RendererAPI::GetAPI(); }
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    
    };
}