#pragma once

#include "Grape/Core/IWindow.h"

#include <GLFW/glfw3.h>
#include "Grape/Renderer/IGraphicsContext.h"

namespace Grape
{
    class WindowsWindow : public IWindow
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override;
        unsigned int GetHeight() const override;

        void SetEventCallback(const EventCallbackFn& callback) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        void* GetNativeWindow() const override { return m_window; }

    private: 
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_window;
        IGraphicsContext* m_context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_data;
    };
}

