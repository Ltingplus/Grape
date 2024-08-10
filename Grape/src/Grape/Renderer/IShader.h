#pragma once

#include <string>

namespace Grape
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

        static IShader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);

        virtual void Bind() const = 0;
        virtual void unBind() const = 0;

    };
}