#pragma once

#include "Core.h"
#include "Events/IEvent.h"
#include "Timestep.h"

namespace Grape
{
    class GRAPE_API ILayer
    {
    public:
        ILayer(const std::string& name = "Layer");
        virtual ~ILayer() {}

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnEvent(IEvent& event) {}

        const std::string& GetName() const { return m_debugName; }

    protected:
        std::string m_debugName;
    };


}
