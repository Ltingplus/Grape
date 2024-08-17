#pragma once
#include <string>
#include "Grape/Core/Core.h"

namespace Grape
{
    class ITexture
    {
    public:
        virtual ~ITexture() = default;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

    };

	class ITexture2D : public ITexture
	{
	public:
        static Ref<ITexture2D> Create(const std::string& path);

	};


}

