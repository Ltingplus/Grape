#pragma once

#include "Core.h"
#include "ILayer.h"

namespace Grape
{
	class GRAPE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(ILayer* layer);
		void PushOverlayer(ILayer* layer);
		void PopLayer(ILayer* layer);
		void PopOverlayer(ILayer* layer);

		std::vector<ILayer*>::iterator begin() { return m_layers.begin(); }
		std::vector<ILayer*>::iterator end() { return m_layers.end(); }

	private:
		std::vector<ILayer*> m_layers;
		std::vector<ILayer*>::iterator m_layerItr;
	};
}
