#pragma once
#include <functional>
#include <future>

namespace archt {

	template<class T>
	class Thread {

		std::function<T(void)> func;
		std::future<T> thread;

	public:
		Thread() {

		}

		Thread(std::function<T(void)> func, bool launch) : func(func) {
			if (launch)
				start();
		}
		
		~Thread() {

		}

		void start() {
			thread = std::async(std::launch::async, func);
		}


		void setFunction(std::function<T(void)> func) {
			this->func = func;
		}

		bool isDone() {
			if (thread.valid())
				return thread.wait_for(std::chrono::duration<int, std::milli>(0)) == std::future_status::ready;
			
			return false;
		}

	
		T result() {
			return thread.get();
		}

		
	};

}