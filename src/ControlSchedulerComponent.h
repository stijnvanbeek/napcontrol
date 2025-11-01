#pragma once

#include <ControlComponent.h>
#include <componentptr.h>
#include <nap/signalslot.h>

namespace nap
{

	// Forward declarations
	class ControlSchedulerComponentInstance;
	class ControlService;

	/**
	 * Add this component to an entity that contains components that need to run on the control thread.
	 * Add the component that needs to be called on the control thread to the mComponents property.
	 * The order of the ControlComponents in this property determines the order of execution of their control methods.
	 */
	class NAPAPI ControlSchedulerComponent : public Component
	{
		RTTI_ENABLE(Component)
		DECLARE_COMPONENT(ControlSchedulerComponent, ControlSchedulerComponentInstance)
	public:
		std::vector<ComponentPtr<ControlComponent>> mComponents; ///< Property: 'Components' Components that need to be updated on the control thread. The control() method will be called on each component in the order in which they appear in the vector.
	};


	class ControlSchedulerComponentInstance : public ComponentInstance
	{
		RTTI_ENABLE(ComponentInstance)
	public:
		ControlSchedulerComponentInstance(EntityInstance& entity, Component& resource)
			: ComponentInstance(entity, resource) { }

		// Inherited from ComponentInstance
		bool init(utility::ErrorState& errorState) override;
		void onDestroy() override;

	private:
		Slot<double> mControlSlot = { this, &ControlSchedulerComponentInstance::control };
		void control(double deltaTime);

		std::vector<ComponentInstancePtr<ControlComponent>> mComponents = initComponentInstancePtr(this, &ControlSchedulerComponent::mComponents);

		ControlService* mControlService = nullptr;
	};

} // namespace nap