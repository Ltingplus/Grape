#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Grape
{    

    class Renderer
    {
    public:
        static RendererAPI::Api GetAPI() { return RendererAPI::GetAPI(); }
        static void BeginScene(const OrthographicCamera& carema);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
    
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData* s_sceneData;
    };
}