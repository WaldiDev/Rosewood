#include "Pch.h"
#include "LayerStack.h"
#include "Layer.h"
#include "Log.h"

namespace rw
{
	LayerStack::LayerStack()
		: mLayers()
		, mLayerInsert(mLayers.begin())
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : mLayers)
		{
			delete layer;
		}

		mLayers.clear();
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		RW_CORE_TRACE("Push layer {0}", layer->GetName());

		mLayerInsert = mLayers.emplace(mLayerInsert, layer);
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		RW_CORE_TRACE("Push overlay {0}", layer->GetName());
		mLayers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		RW_CORE_TRACE("Pop layer {0}", layer->GetName());

		LayerStackIterater layerIter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (layerIter != mLayers.end())
		{
			mLayers.erase(layerIter);
			--mLayerInsert;
		}
		else
		{
			RW_CORE_WARN("Pop layer {0} failed", layer->GetName());
		}
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		RW_CORE_TRACE("Pop overlay {0}", layer->GetName());

		LayerStackIterater layerIter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (layerIter != mLayers.end())
		{
			mLayers.erase(layerIter);
		}
		else
		{
			RW_CORE_WARN("Pop overlay {0} failed", layer->GetName());
		}
	}

}