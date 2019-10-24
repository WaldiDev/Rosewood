#pragma once

#include <string>

#include "Rosewood/Core.h"

namespace rw
{
	class Event;

	class ROSEWOOD_API Layer
	{
	public:
		explicit Layer(const std::string& name)
			: mName(name) 
		{}

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return mName; }

	protected:
		std::string mName;
	};
}
