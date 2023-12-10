#include <gtest/gtest.h>

#include <chrono>
#include <iostream>

#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

TEST(lfsrcrypto_tests, lin_comp_tests) {
    // 0101101001 L = 5
    // 011011011111 L = 8
    // 10011100 L = 6
    EXPECT_EQ(lfsrcrypto::get_linear_complexity("10011100"), 6);
}

TEST(lfsrcrypto_tests, comb_gen_lin_comp_time_test1) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[1]*mem[2] + mem[2];};
    std::vector<std::string_view> comb_gen = {"11001001","10101010","11001101"};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Lin comp = " << lin_comp << ", Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

TEST(lfsrcrypto_tests, comb_gen_lin_comp_time_test_par1) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[1]*mem[2] + mem[2];};
    std::vector<std::string_view> comb_gen = {"11001001","10101010","11001101"};
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, true);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Lin comp = " << lin_comp << ", Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
}

//TEST(lfsrcrypto_tests, comb_gen_lin_comp_time_test_big) {
//    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[1]*mem[2] + mem[2];};
//    std::vector<std::string_view> comb_gen = {"11001001","10101010","11001101"};
//    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//    auto lin_comp = get_linear_complexity_for_comb_gen(comb_gen, func);
//    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//    std::cout << "Lin comp = " << lin_comp << ", Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
//}
//
//TEST(lfsrcrypto_tests, comb_gen_lin_comp_time_test_par_big) {
//    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[1]*mem[2] + mem[2];};
//    std::vector<std::string_view> comb_gen = {"11001001","10101010","11001101"};
//    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//    auto lin_comp = get_linear_complexity_for_comb_gen(comb_gen, func);
//    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//    std::cout << "Lin comp = " << lin_comp << ", Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
//}
