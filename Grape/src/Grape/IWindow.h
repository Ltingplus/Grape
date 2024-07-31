#pragma once

#include "gppch.h"

#include "Grape/Core.h"
#include "Grape/Events/IEvent.h"

namespace Grape
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Grape Engine",
            unsigned int width = 1280,
            unsigned int height = 720)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    class GRAPE_API IWindow
    {
    public:        
        virtual ~IWindow() {}

    public:
        static IWindow* Create(const WindowProps& props = WindowProps());

        using EventCallbackFn = std::function<void(IEvent&)>;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

    };
    
}