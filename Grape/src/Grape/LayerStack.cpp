#include "gppch.h"
#include "LayerStack.h"


namespace Grape
{
    LayerStack::LayerStack()
    {

    }

    LayerStack::~LayerStack()
    {
        for (ILayer* layer : m_layers)
            delete layer;
    }

    void LayerStack::PushOverlayer(ILayer* layer)
    {
        m_layers.emplace_back(layer);
        layer->OnAttach();
    }

    void LayerStack::PopOverlayer(ILayer* layer)
    {
        auto it = std::find(m_layers.begin() + m_layerInsertIndex, m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->OnDetach();
            m_layers.erase(it);
        }
    }

    void LayerStack::PushLayer(ILayer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
        m_layerInsertIndex++;
        layer->OnAttach();
    }

    void LayerStack::PopLayer(ILayer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer);
        if (it != m_layers.end())
        {
            layer->OnDetach();
            m_layers.erase(it);
            m_layerInsertIndex--;
        }
    }

}
