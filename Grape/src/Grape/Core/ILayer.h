#pragma once

#include "Core.h"
#include "Grape/Events/IEvent.h"
#include "Grape/Utils/Timestep.h"

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
        virtual void OnImGuiRender() {}

        const std::string& GetName() const { return m_debugName; }

    protected:
        std::string m_debugName;
    };


}
