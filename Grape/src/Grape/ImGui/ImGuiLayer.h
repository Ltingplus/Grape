#pragma once

#include "Grape/Core/ILayer.h"
#include "Grape/Events/MouseEvent.h"
#include "Grape/Events/KeyEvent.h"
#include "Grape/Events/ApplicationEvent.h"

namespace Grape
{
    /* 
    * @brief ���Ի�ͼ�㣬������������Ķ���
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

