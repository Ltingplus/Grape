#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"


namespace Grape
{
    class RendererAPI
    {
    public:
        enum class Api
        {
            None = 0,
            OpenGL = 1
        };

    public:
        static Api GetAPI()
        {
            return s_API;
        }

        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

    private:
        static Api s_API;

    };
}