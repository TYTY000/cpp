#include <iostream>
#include <list>

#ifdef MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

int main() {
    // 创建一个 doctest::Context 对象
    doctest::Context context;

    // 设置为默认断言上下文，以便在非测试上下文中使用断言
    context.setAsDefaultForAssertsOutOfTestCases();

    // 注册一个断言处理函数（可选）
    context.setAssertHandler([](const doctest::AssertData&) {
        std::cerr << "Assertion failed!\n";
        std::abort();
    });

    // 使用断言
    DOCTEST_REQUIRE(1 ==
                    2);  // 这将触发断言并调用 setAssertHandler 中的处理函数

    return context.run();  // 运行所有测试用例（如果有的话）
}

#else

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>

#include "doctest.h"

using namespace std;
#include <string>

TEST_SUITE_BEGIN("TEMPLATE");
TEST_CASE_TEMPLATE("TEMPLATE1", T, char, short, int, long long int) {
    T var = T();
    --var;
    CHECK(var == -1);
}

TEST_CASE_TEMPLATE_DEFINE("TEMPLATE2", T, test_id) {
    T var = T();
    --var;
    CHECK(var == -1);
}

TEST_CASE_TEMPLATE_INVOKE(test_id, char, short, int, long long int);

TEST_CASE_TEMPLATE_APPLY(test_id, std::tuple<float, double>);
TEST_SUITE_END;

#define DOCTEST_VALUE_PARAMETERIZED_DATA(data, data_container)                 \
    for (auto& data : data_container)                                          \
    DOCTEST_SUBCASE((std::string(#data_container "[") +                        \
                     std::to_string(&data - &(*data_container.begin())) + "]") \
                        .c_str())

TEST_CASE("ITER") {
    int i;
    std::list<int> list = {
        1, 2, 3, 4};  // must be iterable - std::vector<> would work as well

    DOCTEST_VALUE_PARAMETERIZED_DATA(i, list) { cout << i << endl; }
}

bool login(const std::string& username, const std::string& password) {
    return username == "user" && password == "pass";
}
SCENARIO("User attempts to login") {
    GIVEN("A user with correct credentials") {
        std::string username = "user";
        std::string password = "pass";
        WHEN("The user tries to login with correct credentials") {
            bool result = login(username, password);
            THEN("Login should succeed") { CHECK(result == true); }
        }
        WHEN("The user tries to login with incorrect password") {
            std::string wrongPassword = "wrongpass";
            bool result = login(username, wrongPassword);
            THEN("Login should fail") { CHECK(result == false); }
        }
    }
}

#include <thread>

void run_subcases() {
    SUBCASE("Thread level subcase") { CHECK(true); }
}

TEST_CASE("MT" * doctest::description("shouldn't take more than 500ms") *
          doctest::timeout(0.5)) {
    std::thread t1(run_subcases);
    std::thread t2(run_subcases);

    // this_thread::sleep_for(500ms);
    t1.join();
    t2.join();
}

TEST_CASE("FP") {
    REQUIRE(22.0 / 7 ==
            doctest::Approx(3.141).epsilon(0.01));  // allow for a 1% error
    REQUIRE(22.0 / 7 == doctest::Approx(3.141).scale(2).epsilon(
                            0.01));  // allow for a 0.001 error
}

TEST_CASE("IIFE") {
    CHECK_THROWS_MESSAGE([&]() { throw std::runtime_error("error"); }(),
                         "expected exception");
    CHECK_THROWS_AS([&]() { throw std::runtime_error("error"); }(),
                    std::runtime_error);
}

TEST_CASE("CHECK_MSG") {
    int a = 3, b = 2, c = 1;
    INFO("this is relevant to all asserts, and here is some var: ", "local");

    CHECK_MESSAGE(a < b, "relevant only to this assert ", "other_local",
                  " more text!");

    CHECK(b < c);  // here only the first INFO() will be relevant
}

// DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_BEGIN
#include <exception>
#include <mutex>
#include <stdexcept>
#include <thread>
// DOCTEST_MAKE_STD_HEADERS_CLEAN_FROM_WARNINGS_ON_WALL_END

DOCTEST_MSVC_SUPPRESS_WARNING(
    4626)  // assignment operator was implicitly defined as deleted

TEST_CASE("threads...") {
    auto call_from_thread = [](int value) {
        INFO("print me!");
        // one of these has to fail
        CHECK(value == 1);
        CHECK(value == 2);
    };

    int data_1 = 1;
    int data_2 = 2;
    CAPTURE(data_1);  // will not be used for assertions in other threads

    // subcases have to be used only in the main thread (where the test
    // runner thread is)
    SUBCASE("test runner thread") { call_from_thread(data_1); }

    // normal threads which are assumed not to throw
    SUBCASE("spawned threads") {
        std::thread t1(call_from_thread, data_1);
        std::thread t2(call_from_thread, data_2);

        t1.join();
        t2.join();
    }

    // exceptions from threads (that includes failing REQUIRE asserts) have
    // to be handled explicitly
    SUBCASE("spawned threads with exception propagation") {
        std::exception_ptr exception_ptr = nullptr;
        std::mutex mutex;

        auto might_throw = [&]() {
            try {
                REQUIRE(1 == 1);
                REQUIRE(1 == 2);  // will fail and throw an exception
                MESSAGE("not reached!");
            } catch (...) {
                // make sure there are no races when dealing with the
                // exception ptr
                std::unique_lock lock(mutex);

                // set the exception pointer in case of an exception - might
                // overwrite another exception but here we care about
                // propagating any exception - not all
                exception_ptr = std::current_exception();
            }
        };
        std::thread t1(might_throw);
        std::thread t2(might_throw);

        t1.join();
        t2.join();

        // if any thread has thrown an exception - rethrow it
        if (exception_ptr) std::rethrow_exception(exception_ptr);
    }
}

TEST_CASE("lots of nested subcases") {
    cout << endl << "root" << endl;
    SUBCASE("") {
        cout << "1" << endl;
        SUBCASE("") { cout << "1.1" << endl; }
    }
    SUBCASE("") {
        cout << "2" << endl;
        SUBCASE("") { cout << "2.1" << endl; }
        SUBCASE("") {
            cout << "2.2" << endl;
            SUBCASE("") {
                cout << "2.2.1" << endl;
                SUBCASE("") { cout << "2.2.1.1" << endl; }
                SUBCASE("") { cout << "2.2.1.2" << endl; }
            }
        }
        SUBCASE("") { cout << "2.3" << endl; }
        SUBCASE("") { cout << "2.4" << endl; }
    }
}

TEST_CASE("vectors can be sized and resized") {
    std::vector<int> v(5);
    // 1
    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    SUBCASE("adding to the vector increases it's size") {
        // 2
        v.push_back(1);

        CHECK(v.size() == 6);
        CHECK(v.capacity() >= 6);
    }
    SUBCASE("reserving increases just the capacity") {
        // 3
        v.reserve(6);

        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 6);
    }
}
TEST_SUITE("math") {
    TEST_CASE("1") {}  // part of the math test suite
    TEST_CASE("2") {}  // part of the math test suite
}

#endif  // MAIN
