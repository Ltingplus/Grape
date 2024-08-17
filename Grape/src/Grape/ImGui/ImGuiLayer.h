#pragma once

#include "Grape/Core/ILayer.h"
#include "Grape/Events/MouseEvent.h"
#include "Grape/Events/KeyEvent.h"
#include "Grape/Events/ApplicationEvent.h"

namespace Grape
{
    /* 
    * @brief 调试绘图层，绘制在其他层的顶部
    */
    class GRAPE_API ImGuiLayer : public ILayer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

    private:
        float m_time = 0.0f;
    };
}

