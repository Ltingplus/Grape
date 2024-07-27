#pragma once
#include "IEvent.h"

#include <sstream>

namespace Grape
{
	class GRAPE_API KeyEvent : public IEvent
	{
	public:
		int GetKeyCode() const { return m_keyCode; }

	protected:
		KeyEvent(int keyCode)
			:m_keyCode(keyCode)
		{}

	protected:
		int m_keyCode;
	};

	class GRAPE_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keyCode, int repeatCount)
			:KeyEvent(keyCode)
			, m_repeatCount(repeatCount)
		{}

		int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;
	};

	class GRAPE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			:KeyEvent(keyCode)
		{}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}