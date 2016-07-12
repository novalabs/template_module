/* COPYRIGHT (c) 2016 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <Core/MW/Middleware.hpp>

#include "ch.h"
#include "hal.h"

#include <Core/HW/GPIO.hpp>
#include <Core/MW/Thread.hpp>
#include <Module.hpp>


using LED_PAD = Core::HW::Pad_<Core::HW::GPIO_F, LED_PIN>;
static LED_PAD _led;

static THD_WORKING_AREA(wa_info, 1024);
static Core::MW::RTCANTransport rtcantra(RTCAND1);

RTCANConfig rtcan_config = {
	1000000, 100, 60
};

#ifndef CORE_MODULE_NAME
#define CORE_MODULE_NAME "XXX"
#endif

Core::MW::Middleware Core::MW::Middleware::instance(CORE_MODULE_NAME, "BOOT_" CORE_MODULE_NAME);

Module::Module()
{}

bool
Module::initialize()
{
//	CORE_ASSERT(Core::MW::Middleware::instance.is_stopped()); // TODO: capire perche non va...

	static bool initialized = false;

	if (!initialized) {
		halInit();
		chSysInit();

		Core::MW::Middleware::instance.initialize(wa_info, sizeof(wa_info), Core::MW::Thread::LOWEST);
		rtcantra.initialize(rtcan_config);
		Core::MW::Middleware::instance.start();

		initialized = true;
	}

	return initialized;
} // Board::initialize

// Leftover from CoreBoard (where LED_PAD cannot be defined
void
Core::MW::CoreModule::Led::toggle()
{
	_led.toggle();
}

void
Core::MW::CoreModule::Led::write(
		unsigned on
)
{
	_led.write(on);
}
