#pragma once
#include "Grape/Renderer/VertexArray.h"

namespace Grape
{
    class OpenGLVertexArray : public VertexArray
    {

    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

    private:
        uint32_t m_rendererId;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}
