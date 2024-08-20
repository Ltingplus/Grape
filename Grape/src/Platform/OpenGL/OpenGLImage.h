#pragma once

#include "Grape/Core/IImage.h"
#include "glad/glad.h"

namespace Grape
{
    class OpenGLImage : public IImage
    {
    public:
        OpenGLImage(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr);
        ~OpenGLImage();

        void SetData(const void* data) override;

        uint32_t GetTextureID() const override { return m_textureID; }

        void Resize(uint32_t width, uint32_t height) override;

        uint32_t GetWidth() const override { return m_width; }
        uint32_t GetHeight() const override { return m_height; }


    private:
        uint32_t m_width = 0, m_height = 0;        
        ImageFormat m_format = ImageFormat::None;
        GLuint m_textureID;
    };

}

