#pragma once
#include <thread>
#include <future>

namespace archt {

	class Thread {

		std::future<void> future;

	public:
		Thread() {

		}


		~Thread() {

		}

		void start() {
		}

		bool isDone() const {
			return false;
		}

		void setFunction() {
		}
	};


}