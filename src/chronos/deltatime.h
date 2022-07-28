#pragma once
#include <chrono>

namespace archt {

	class DeltaTime {

		std::chrono::system_clock::time_point last;
		std::chrono::system_clock::time_point now;
		int64_t delta;



	public:
		DeltaTime();
		~DeltaTime();

		void update();

		int64_t getNanos() const;
		double getMicros() const;
		double getMillis() const;
		double getSeconds() const;


	};


}