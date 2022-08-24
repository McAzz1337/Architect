#pragma once

#include <iostream>
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

namespace archt {

	class GuiWindow {

	public:
		GuiWindow() = default;
		virtual ~GuiWindow();
		virtual void render() = 0;
	};


	

	class GuiWindowVoid : public GuiWindow {
		
		std::function<void()> f;
	public:
		GuiWindowVoid(std::function<void()> func);
	
		void render() override;
	};

	template <typename F, typename... Ts>
	class GuiWindowArgs : public GuiWindow {
		static_assert(!(std::is_rvalue_reference_v<Ts> && ...));
	private:
		F f;
		std::tuple<Ts...> args;
	public:

		template <typename FwdF, typename... FwdTs,
			typename = std::enable_if_t<(std::is_convertible_v<FwdTs&&, Ts> && ...)>>
			GuiWindowArgs(FwdF&& func, FwdTs&&... args)
			: f(std::forward<FwdF>(func)),
			args{ std::forward<FwdTs>(args)... }
		{}

		void render() override {
			std::apply(f, args);
		}
	};

	template <typename F, typename... Args>
	auto createGuiWindowArgs(F&& f, Args&&... args) {

		return new GuiWindowArgs<std::decay_t<F>, std::remove_cv_t<std::remove_reference_t<Args>>...>
			(std::forward<F>(f), std::forward<Args>(args)...);
	}



}