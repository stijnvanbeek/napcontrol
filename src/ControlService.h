#pragma once

#include <ControlThread.h>

#include <nap/service.h>
#include <component.h>


namespace nap
{

	class ControlService;

	class NAPAPI ControlServiceConfiguration : public ServiceConfiguration
	{
		RTTI_ENABLE(ServiceConfiguration)
	public:
		ControlServiceConfiguration() = default;
		rtti::TypeInfo getServiceType() const override { return RTTI_OF(ControlService); }

		float mDesiredControlRate = 60.f; ///< Property: 'DesiredControlRate' The control rate cap in HZ
	};


    /**
     * Service that takes care of a control thread that runs parallel to the main thread on an independent control rate.
     */
	class NAPAPI ControlService : public Service
	{
		RTTI_ENABLE(Service)

	public:
		ControlService(ServiceConfiguration* configuration) : Service(configuration) { }

		// Inherited from Service
		bool init(utility::ErrorState& error) override;
        void postResourcesLoaded() override;
		void preShutdown() override;
		void shutdown() override;

		/**
		 * Sets the desired control rate for the control thread and saves the value to the configuration
		 * @param controlRate The desired optimal control rate. If the system performance can't keep up the real control rate will drop below.
		 */
		void setDesiredControlRate(float controlRate);

		/**
		 * @return The desired control rate in Hz
		 */
		float getDesiredControlRate() const { return mControlThread.getDesiredControlRate(); }

		/**
		 * @return The control thread
		 */
		ControlThread& getControlThread() { return mControlThread; }

	private:
		ControlThread mControlThread;
	};


}

