#include "gppch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Grape
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Grape::ShaderDataType::Float:        return GL_FLOAT;
        case Grape::ShaderDataType::Float2:        return GL_FLOAT;
        case Grape::ShaderDataType::Float3:        return GL_FLOAT;
        case Grape::ShaderDataType::Float4:        return GL_FLOAT;
        case Grape::ShaderDataType::Int:        return GL_INT;
        case Grape::ShaderDataType::Int2:        return GL_INT;
        case Grape::ShaderDataType::Int3:        return GL_INT;
        case Grape::ShaderDataType::Int4:        return GL_INT;
        case Grape::ShaderDataType::Mat3:        return GL_FLOAT;
        case Grape::ShaderDataType::Mat4:        return GL_FLOAT;
        default:
            break;
        }
        GP_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_rendererId);
    }

    
    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_rendererId);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        GP_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no layout!");

        glBindVertexArray(m_rendererId);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type)
                , element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
            ++index;
        }

        m_vertexBuffers.emplace_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererId);
        indexBuffer->Bind();

        m_indexBuffer = indexBuffer;
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const
    {
        return m_vertexBuffers;
    }

    const std::shared_ptr<Grape::IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_indexBuffer;
    }

}