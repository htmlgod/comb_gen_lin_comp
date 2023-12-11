#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <numeric>

#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

#define SMALL 64
#define MEDIUM 128
#define LARGE 256
#define GIANT 512

TEST(lfsrcrypto_tests, lin_comp_tests) {
    // 0101101001 L = 5
    // 011011011111 L = 8
    //EXPECT_EQ(lfsrcrypto::get_linear_complexity("0101101001"), 5);
    EXPECT_EQ(lfsrcrypto::get_linear_complexity("10011100"), 6);
}

TEST(comb_gen_lin_comp_tests, threads_3_regs_64bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[0]*mem[2] + mem[1]*mem[2];};
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 3; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(SMALL));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::THREADS);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, threads_64_regs_128bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 64; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(MEDIUM));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::THREADS);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}
TEST(comb_gen_lin_comp_tests, threads_128_regs_256bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 128; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(LARGE));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::THREADS);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}
TEST(comb_gen_lin_comp_tests, threads_256_regs_512bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 256; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(GIANT));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::THREADS);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, async_3_regs_64bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[0]*mem[2] + mem[1]*mem[2];};
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 3; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(SMALL));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::ASYNC);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, async_64_regs_128bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 64; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(MEDIUM));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::ASYNC);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, async_128_regs_256bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 128; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(LARGE));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::ASYNC);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}
TEST(comb_gen_lin_comp_tests, async_256_regs_512bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 256; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(GIANT));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::ASYNC);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, openmp_3_regs_64bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { return mem[0]*mem[1] + mem[0]*mem[2] + mem[1]*mem[2];};
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 3; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(SMALL));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::OPENMP);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, openmp_64_regs_128bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 64; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(MEDIUM));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::OPENMP);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}

TEST(comb_gen_lin_comp_tests, openmp_128_regs_256bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 128; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(LARGE));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::OPENMP);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}
TEST(comb_gen_lin_comp_tests, openmp_256_regs_512bits_gamma) {
    auto func = [](const std::vector<size_t>& mem) { 
        return std::accumulate(mem.begin(), mem.end(), 0);
    };
    std::vector<std::string> comb_gen;
    for (size_t i = 0; i < 256; i++)
        comb_gen.push_back(lfsrcrypto::gen_rand_gamma(GIANT));
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "-- : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        auto lin_comp = lfsrcrypto::get_linear_complexity_for_comb_gen(comb_gen, func, lfsrcrypto::EXEC_TYPE::OPENMP);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cerr << "|| : Lin comp = " << lin_comp << ", Time = " 
            << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
    }
}
