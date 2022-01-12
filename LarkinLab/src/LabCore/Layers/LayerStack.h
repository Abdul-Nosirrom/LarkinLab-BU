#pragma once

#include "LabCore/Core.h"
#include "Layer.h"

#include <vector>

namespace LarkinLab
{
	/// <summary>
	/// Essentially acts as a wrapper over the vector m_Layers
	/// </summary>
	class LL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		/// <summary>
		/// LayerInsert keeps track of where our last layer is in the vector as a way to differentiate
		/// between our application layers and overlays - only gets updated with layer operations not
		/// overlay operations
		/// </summary>
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}

