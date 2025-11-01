#include "ControlSchedulerComponent.h"

#include <ControlService.h>
#include <nap/core.h>

RTTI_BEGIN_CLASS(nap::ControlSchedulerComponent)
	RTTI_PROPERTY("Components", &nap::ControlSchedulerComponent::mComponents, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::ControlSchedulerComponentInstance)
	RTTI_CONSTRUCTOR(nap::EntityInstance&, nap::Component&)
RTTI_END_CLASS

namespace nap
{

	bool ControlSchedulerComponentInstance::init(utility::ErrorState& errorState)
	{
		mControlService = getEntityInstance()->getCore()->getService<ControlService>();
		mControlService->getControlThread().connectPeriodicTask(mControlSlot);
		return true;
	}


	void ControlSchedulerComponentInstance::onDestroy()
	{
		mControlService->getControlThread().disconnectPeriodicTask(mControlSlot);
	}


	void ControlSchedulerComponentInstance::control(double deltaTime)
	{
		for (auto& component : mComponents)
			component->control(deltaTime);
	}


} // namespace nap