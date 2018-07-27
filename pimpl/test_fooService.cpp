
#include "fooService.hpp"

#include <cstring>
#include <cassert>

void TestFooService_TestNull() {
    FooService service{};
    auto result = service.stripSuffix("something");
    assert(
        0 == strcmp("asd",result.c_str())
    );
}

int main(int argc, char **argv) {
    TestFooService_TestNull();
    return 0;
}