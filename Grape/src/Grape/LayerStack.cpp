#include "gppch.h"
#include "LayerStack.h"


namespace Grape
{
	LayerStack::LayerStack()
		: m_layerItr(m_layers.begin())
	{

	}

	LayerStack::~LayerStack()
	{
		for (ILayer* layer : m_layers)
			delete layer;
	}

	void LayerStack::PushLayer(ILayer* layer)
	{
		m_layerItr = m_layers.emplace(m_layerItr, layer);
	}

	void LayerStack::PushOverlayer(ILayer* layer)
	{
		m_layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(ILayer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerItr--;
		}
	}

	void LayerStack::PopOverlayer(ILayer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}

}
