#include <coroutine>
#include <exception>
#include <iostream>
struct Generator {
    struct promise_type {
        int current_value;
        auto get_return_object() {
            return Generator{Handle::from_promise(*this)};
        }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto return_void() {}
        auto yield_value(int value) {
            current_value = value;
            return std::suspend_always{};
        }
        void unhandled_exception() { std::terminate(); }
    };
    using Handle = std::coroutine_handle<promise_type>;
    Handle handle;
    Generator(Handle h) : handle(h) {}
    ~Generator() {
        if (handle) handle.destroy();
    }
    bool next() {
        handle.resume();
        return !handle.done();
    }
    int value() { return handle.promise().current_value; }
};

Generator generate() {
    for (int i = 0; i < 3; ++i) co_yield i;
}

int main(int argc, char *argv[]) {
    // int a = 10;
    // auto lambda = [a]() mutable { return ++a; };  // 值捕获并可修改
    // auto lambda_ref = [&a]() { return ++a; };     // 引用捕获
    // std::cout << lambda() << '\t' << lambda_ref() << std::endl;
    auto gen = generate();  // 调用生成器函数
    while (gen.next()) {
        std::cout << gen.value() << std::endl;  // 输出 yield 的值
    }
    return 0;
}
