#pragma once

#include "Grape/Core.h"

#include "gppch.h"

namespace Grape
{
    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate, 
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed, 
        MouseButtonReleased, 
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication     = BIT(0),
        EventCategoryInput             = BIT(1),
        EventCategoryKeyboard         = BIT(2),
        EventCategoryMouse             = BIT(3),
        EventCategoryMouseButton     = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
                                virtual EventType GetEventType() const override {return GetStaticType();}\
                                virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

    class GRAPE_API IEvent
    {
        friend class EventDispatcher;

    public:
        virtual ~IEvent() {}
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        virtual bool IsHandled() const { return m_handled; }

        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        inline std::ostream& operator<<(std::ostream& os)
        {
            return os << ToString();
        }

    protected:
        bool m_handled = false; // �¼��Ƿ񱻴�����������ٴ���
    };


    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        EventDispatcher(IEvent& event)
            : m_event(event)
        {
        }

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.m_handled = func(*(T*)&m_event);
                return true;
            }
            return false;
        }

    private:
        IEvent& m_event;
    };
    
}