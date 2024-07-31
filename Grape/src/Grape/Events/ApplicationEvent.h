#pragma once

#include "IEvent.h"


namespace Grape
{
    class GRAPE_API WindowResizeEvent : public IEvent
    {
    public:
         WindowResizeEvent(unsigned int width, unsigned int height)
             : m_width(width)
             , m_height(height)
         {}

         unsigned int GetWidth() const { return m_width; }
         unsigned int GetHeight() const { return m_height; }

         std::string ToString() const override
         {
             std::stringstream ss;
             ss << "WindowResizeEvent: " << m_width << ", " << m_height;
             return ss.str();
         }

         EVENT_CLASS_TYPE(WindowResize)
         EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        unsigned int m_width;
        unsigned int m_height;

    };

    class GRAPE_API WindowCloseEvent : public IEvent
    {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class GRAPE_API AppUpdateEvent : public IEvent
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class GRAPE_API AppRenderEvent : public IEvent
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

}