#include "gppch.h"
#include "OpenGLTexture.h"

#include "stb_image/stb_image.h"

namespace Grape
{

    OpenGLTexture::OpenGLTexture(const std::string& path)
        : m_path(path)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        GP_CORE_ASSERT(data, "Failed to load image!");
        m_width = width;
        m_height = height;

        if (channels == 4)
        {
            m_internalFormat = GL_RGBA8;
            m_dataFormat = GL_RGBA;
        }        
        else if (channels == 3)
        {
            m_internalFormat = GL_RGB8;
            m_dataFormat = GL_RGB;
        }
        GP_CORE_ASSERT(m_internalFormat & m_dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderId);
        glTextureStorage2D(m_renderId, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_renderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_renderId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_renderId, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_renderId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
        : m_width(width)
        , m_height(height)
    {

        m_internalFormat = GL_RGBA;
        m_dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderId);
        glTextureStorage2D(m_renderId, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_renderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_renderId, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_renderId, GL_TEXTURE_WRAP_T, GL_REPEAT);

    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_renderId);
    }

    void OpenGLTexture::SetData(void* data, uint32_t size)
    {
        uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
        GP_CORE_ASSERT(size == bpp * m_width * m_height, "Data must be entire texture!");
            
        glTextureSubImage2D(m_renderId, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);

    }

    void OpenGLTexture::Bind(uint32_t slot /*= 0*/) const
    {
        glBindTextureUnit(slot, m_renderId);
    }

}