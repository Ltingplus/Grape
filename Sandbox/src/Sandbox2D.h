#pragma once

#include "Grape.h"

    class Sandbox2D : public Grape::ILayer
    {
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Grape::Timestep ts) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Grape::IEvent& e) override;
    private:
        Grape::OrthographicCameraController m_cameraController;

        // Temp
        Grape::Ref<Grape::VertexArray> m_squareVA;
        Grape::Ref<Grape::IShader> m_flatColorShader;
        Grape::Ref<Grape::ITexture2D> m_checkerboardTexture;

        glm::vec4 m_squareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
    };


