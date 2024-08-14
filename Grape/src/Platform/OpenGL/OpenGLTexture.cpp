#include "gppch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
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

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }        
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }
        GP_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_renderId);
        glTextureStorage2D(m_renderId, 1, internalFormat, m_width, m_height);

        glTextureParameteri(m_renderId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_renderId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
        glTextureSubImage2D(m_renderId, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_renderId);
    }

    void OpenGLTexture::Bind(uint32_t slot /*= 0*/) const
    {
        glBindTextureUnit(slot, m_renderId);
    }

}