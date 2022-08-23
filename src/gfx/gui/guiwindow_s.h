#pragma once

#include <iostream>
#include <tuple>
#include <functional>
#include <utility>
#include <type_traits>

namespace archt {

    class BaseWindow {

    public:
        BaseWindow() = default;
        virtual ~BaseWindow();
        virtual void render() = 0;
    };


    class GuiWindow_t : public BaseWindow {

        std::function<void()> func;
    public:
        GuiWindow_t() = delete;
        GuiWindow_t(std::function<void()> renderFunc);
        ~GuiWindow_t();

        void render() override;
    };

    template <typename F, typename... Ts>
    class GuiWindow_s : public BaseWindow {
        static_assert(!(std::is_rvalue_reference_v<Ts> && ...));
    private:
        F f;
        std::tuple<Ts...> args;
    public:
        template <typename FwdF, typename... FwdTs,
            typename = std::enable_if_t<(std::is_convertible_v<FwdTs&&, Ts> && ...)>>
            GuiWindow_s(FwdF&& func, FwdTs&&... args)
            : f(std::forward<FwdF>(func)),
            args{ std::forward<FwdTs>(args)... }
        {}

        void render() override {
            std::apply(f, args);
        }
    };

    template <typename F, typename... Args>
    auto createGuiWindow(F&& f, Args&&... args) {
        return new GuiWindow_s<std::decay_t<F>, std::remove_cv_t<std::remove_reference_t<Args>>...>
            (std::forward<F>(f), std::forward<Args>(args)...);
    }



}