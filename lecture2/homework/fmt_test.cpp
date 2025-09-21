#include <fmt/format.h>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <iostream>

// code copied from https://fmt.dev/11.2/syntax/
int main(){
    
    //fmt::print
    fmt::print(
        "┌{0:─^{2}}┐\n"
        "│{1: ^{2}}│\n"
        "└{0:─^{2}}┘\n",
        "", "Hello, world!", 20);
    
    //fmt::format
    std::cout << fmt::format(std::locale("en_US.UTF-8"), "{:L}", 1234567890)<<std::endl;
    std::cout << fmt::format("{0}{1}{0}", "abra", "cad")<<std::endl;
    std::cout << fmt::format("{:^30}", "centered") << std::endl;
    std::cout << fmt::format("int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}", 42)<<std::endl;
    
    //fmt::chrono
    auto t = tm();
    t.tm_year = 2010 - 1900;
    t.tm_mon = 7;
    t.tm_mday = 4;
    t.tm_hour = 12;
    t.tm_min = 15;
    t.tm_sec = 58;
    fmt::print("{:%Y-%m-%d %H:%M:%S}\n", t);

    return 0;
}
