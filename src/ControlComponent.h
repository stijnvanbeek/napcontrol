#pragma once

#include <component.h>
#include <entity.h>

namespace nap
{

	// Forward declarations
	class ControlComponentInstance;

	/**
	 * Baseclass for components running on the control thread.
	 * Derive from this component in order to have it updated on the control thread. To make it work:
	 * - Override the derived component instance's control() method.
	 * - Add the control component resource to the mComponents list of a ControlSchedulerComponent
	 */
	class NAPAPI ControlComponent : public Component
	{
		RTTI_ENABLE(Component)
		DECLARE_COMPONENT(ControlComponent, ControlComponentInstance)
	public:
		ControlComponent() = default;
	};


	/**
	 * Instance of ControlComponent.
	 * Override the control method of this instance to define periodic behaviour on the control thread.
	 */
	class ControlComponentInstance : public ComponentInstance
	{
		RTTI_ENABLE(ComponentInstance)
	public:
		ControlComponentInstance(EntityInstance& entity, Component& resource) : ComponentInstance(entity, resource)
		{
		}

		virtual void control(double deltaTime) { }

	private:
	};

} // namespace nap