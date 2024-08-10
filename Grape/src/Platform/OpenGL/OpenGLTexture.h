#pragma once

#include "Grape/Renderer/ITexture.h"

namespace Grape
{
    class OpenGLTexture : public ITexture2D
    {
    public:
        OpenGLTexture(const std::string& path);
        ~OpenGLTexture();

        uint32_t GetWidth() const override { return m_width; }
        uint32_t GetHeight() const override { return m_height; }

        void Bind(uint32_t slot = 0) const override;

    private:
        std::string m_path;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t  m_renderId;
    };
}

