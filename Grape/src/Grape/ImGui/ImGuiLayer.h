#pragma once

#include "Grape/ILayer.h"

namespace Grape
{
	class GRAPE_API ImGuiLayer : public ILayer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(IEvent& event) override;

	private:
		float m_time = 0.0f;
	};
}

