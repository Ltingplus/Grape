#include "gppch.h"
#include "OpenGLImage.h"

namespace Grape
{
    OpenGLImage::OpenGLImage(uint32_t width, uint32_t height, ImageFormat format, const void* data /*= nullptr*/)
        : m_width(width)
        , m_height(height)
        , m_format(format)
    {
        if (data)
            SetData(data);
    }

    OpenGLImage::~OpenGLImage()
    {

    }

    void OpenGLImage::SetData(const void* data)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        GLenum internalFormat;
        GLenum pixelFormat;
        switch (m_format) {
        case ImageFormat::RGBA:
            internalFormat = GL_RGBA8;
            pixelFormat = GL_RGBA;
            break;
        case ImageFormat::RGB:
            internalFormat = GL_RGB8;
            pixelFormat = GL_RGB;
            break;
        default:
            GP_CORE_ASSERT(false, "Unsupported image format");
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, pixelFormat, GL_UNSIGNED_BYTE, data);

        // ��ѡ: �����������
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0); // �������
    }

    void OpenGLImage::Resize(uint32_t width, uint32_t height)
    {
        // 1. �ͷ���������
        glDeleteTextures(1, &m_textureID);
        m_textureID = 0;

        // 2. ���¿�Ⱥ͸߶�
        m_width = width;
        m_height = height;

        // 3. ���´�������
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        // ʹ����ͬ���ڲ���ʽ�����ظ�ʽ
        GLenum internalFormat;
        GLenum pixelFormat;
        switch (m_format) {
        case ImageFormat::RGBA:
            internalFormat = GL_RGBA8;
            pixelFormat = GL_RGBA;
            break;
        case ImageFormat::RGB:
            internalFormat = GL_RGB8;
            pixelFormat = GL_RGB;
            break;
        default:
            GP_CORE_ASSERT(false, "Unsupported image format");
            return;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, pixelFormat, GL_UNSIGNED_BYTE, nullptr);

        // ��ѡ: �����������
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_2D, 0); // �������
    }

}
