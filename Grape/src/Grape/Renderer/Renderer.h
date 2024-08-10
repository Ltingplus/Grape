#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "IShader.h"

namespace Grape
{    

    class Renderer
    {
    public:
        static RendererAPI::Api GetAPI() { return RendererAPI::GetAPI(); }
        static void BeginScene(const OrthographicCamera& carema);
        static void EndScene();

        static void Submit(const std::shared_ptr<IShader>& shader, const std::shared_ptr<VertexArray>& vertexArray
        , const glm::mat4& transform = glm::mat4(1.0f));
    
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };
        static SceneData* s_sceneData;
    };
}