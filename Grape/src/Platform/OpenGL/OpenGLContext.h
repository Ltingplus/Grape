#pragma once

#include "Grape/Renderer/IGraphicsContext.h"

struct GLFWwindow;

namespace Grape
{
    class OpenGLContext : public IGraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };
}
