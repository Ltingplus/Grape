#pragma once
#include "Grape/Renderer/OrthographicCamera.h"
#include "ITexture.h"

namespace Grape
{
    class Renderer2D
    {
    public:
        static void Init();
        static void ShutDown();

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        // primitive
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture);

    };
}

