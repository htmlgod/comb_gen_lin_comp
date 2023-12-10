#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <numeric>

#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

TEST(lfsrcrypto_tests, lin_comp_tests) {
    // 0101101001 L = 5
    // 011011011111 L = 8
    //EXPECT_EQ(lfsrcrypto::get_linear_complexity("0101101001"), 5);
    EXPECT_EQ(lfsrcrypto::get_linear_complexity("10011100"), 6);
}

TEST(comb_gen_lin_comp_tests, basic1) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[0]*mem[2] + mem[1]*mem[2];};
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 3; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(128));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, true);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, basic2) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[1]*mem[2] + mem[2];};
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 3; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(128));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, true);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, large1) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 1024; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(128));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, true);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    }
}

