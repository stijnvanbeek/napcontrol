#include "ControlService.h"

RTTI_BEGIN_CLASS(nap::ControlServiceConfiguration)
	RTTI_PROPERTY("DesiredControlRate", &nap::ControlServiceConfiguration::mDesiredControlRate, nap::rtti::EPropertyMetaData::Default)
RTTI_END_CLASS

RTTI_BEGIN_CLASS_NO_DEFAULT_CONSTRUCTOR(nap::ControlService)
	RTTI_CONSTRUCTOR(nap::ServiceConfiguration*)
RTTI_END_CLASS

namespace nap
{

	bool ControlService::init(utility::ErrorState& error)
	{
		return true;
	}


    void ControlService::postResourcesLoaded()
    {
        mControlThread.setDesiredControlRate(getConfiguration<ControlServiceConfiguration>()->mDesiredControlRate);
        mControlThread.start();
    }


	void ControlService::preShutdown()
	{
		mControlThread.stop();
	}


	void ControlService::shutdown()
	{
	}



	void ControlService::setDesiredControlRate(float controlRate)
	{
		mControlThread.setDesiredControlRate(controlRate);
		auto configuration = getConfiguration<ControlServiceConfiguration>();
		configuration->mDesiredControlRate = controlRate;
	}


}

