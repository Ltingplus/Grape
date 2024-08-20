#pragma once
#include "Core.h"

namespace Grape
{
    enum class ImageFormat
    {
        None = 0,
        RGB,
        RGBA
    };

    class IImage
    {
    public:
        virtual ~IImage() = default;
        
        static Ref<IImage> Create(uint32_t width, uint32_t height, ImageFormat format, const void* data = nullptr);
        
        virtual uint32_t GetTextureID() const = 0;

        virtual void SetData(const void* data) = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

    };
}