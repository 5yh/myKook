#include <iostream>
#include <coroutine>

struct generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        int current_value;

        auto get_return_object() {
            return generator{ handle_type::from_promise(*this) };
        }

        auto initial_suspend() {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept {
            return std::suspend_always{};
        }

        void unhandled_exception() {
            std::terminate();
        }

        auto yield_value(int value) {
            current_value = value;
            return std::suspend_always{};
        }
    };

    bool next() {
        coro.resume();
        return !coro.done();
    }

    int value() const {
        return coro.promise().current_value;
    }

    ~generator() {
        if (coro)
            coro.destroy();
    }

private:
    generator(handle_type h) : coro(h) {}

    handle_type coro;
};

generator generate() {
    co_yield 1;
    co_yield 2;
    co_yield 3;
}

int main() {
    generator gen = generate();
    while (gen.next()) {
        std::cout << gen.value() << std::endl;
    }

    return 0;
}
