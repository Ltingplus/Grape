#pragma once

#include "Grape/IInput.h"

namespace Grape
{

	class WindowsInput : public IInput
	{
	protected:
		virtual  bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}

