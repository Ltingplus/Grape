#pragma once

#include "gppch.h"
#include "Grape/Core.h"

namespace Grape
{
    class GRAPE_API IInput
    {
    public:
        virtual ~IInput() {}

        static bool IsKeyPressed(int keycode) { return s_instance->IsKeyPressedImpl(keycode); }

        static bool IsMouseButtonPressed(int button) { return s_instance->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePosition() { return s_instance->GetMousePositionImpl(); }
        static float GetMouseX() { return s_instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_instance->GetMouseYImpl(); }
    
    protected:
        virtual bool IsKeyPressedImpl(int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:
        static IInput* s_instance;
    };

}