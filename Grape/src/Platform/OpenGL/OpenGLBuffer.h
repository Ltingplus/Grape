#pragma once

#include "Grape/Renderer/Buffer.h"

namespace Grape
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const BufferLayout& layout) override { m_bufferLayout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_bufferLayout; }

    private:
        uint32_t m_rendererID;
        BufferLayout m_bufferLayout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;
        virtual uint32_t GetCount() const { return m_count; }

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };
}