#include <Configuration.hpp>
#include <Module.hpp>

// MESSAGES
#include <common_msgs/Led.hpp>

// NODES
#include <led/Subscriber.hpp>

// BOARD IMPL

// *** DO NOT MOVE ***
Module module;

// TYPES

// NODES
led::Subscriber led_subscriber("led_subscriber", Core::MW::Thread::PriorityEnum::LOWEST);

// MAIN
extern "C" {
	int
	main()
	{
		module.initialize();

		// Led subscriber node
		led_subscriber.configuration.topic = "led";
		module.add(led_subscriber);

		// Setup and run
		module.setup();
		module.run();

		// Is everything going well?
		for (;;) {
			if (!module.isOk()) {
				module.halt("This must not happen!");
			}

			Core::MW::Thread::sleep(Core::MW::Time::ms(500));
		}

		return Core::MW::Thread::OK;
	}
}
