#pragma once

#include "../chronos/delta.h"

#include <tuple>

namespace archt {

	class ScheduledTask {

		float delay = 0.0f;
		delta::archt_time submissionTime;

	public:
		ScheduledTask();
		~ScheduledTask();





	};

	template<typename T, typename ...Args>
	class ScheduledTask_W {

		T function;
		std::tuple<Args...> args;

	public:
		template<typename Tw,
				typename ArgsW,
				typename = std::enable_if<std::is_convertible<ArgsW&&, Args> && ...>>
		ScheduledTask_W(Tw&& func, ArgsW&& args)
			: func(func), args{ std::forward<ArgsW>(args)... } {

		}
		
		~ScheduledTask_W() {
		}

		void operator()() {
			std::apply(function, args);
		}




	};


}