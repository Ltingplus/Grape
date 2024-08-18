#pragma once

#include "Grape/Renderer/ITexture.h"
#include "glad/glad.h"

namespace Grape
{
    class OpenGLTexture : public ITexture2D
    {
    public:
        OpenGLTexture(uint32_t width, uint32_t height);
        OpenGLTexture(const std::string& path);
        ~OpenGLTexture();

        uint32_t GetWidth() const override { return m_width; }
        uint32_t GetHeight() const override { return m_height; }

        virtual void SetData(void* data, uint32_t size) override;

        void Bind(uint32_t slot = 0) const override;

    private:
        std::string m_path;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t  m_renderId;
        GLenum m_internalFormat, m_dataFormat;
    };
}

