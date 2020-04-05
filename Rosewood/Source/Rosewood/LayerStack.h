#pragma once

#include <vector>

#include "Rosewood/Core.h"

namespace rw
{
	class Layer;
	using LayerStackIterater = std::vector<Layer*>::iterator;

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		// iterater operator
		LayerStackIterater begin() { return mLayers.begin(); }
		LayerStackIterater end() { return mLayers.end(); }

	private:
		std::vector<Layer*> mLayers;
		LayerStackIterater mLayerInsert;
	};
}
