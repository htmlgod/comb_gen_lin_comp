#include <gtest/gtest.h>
#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

TEST(LibTest, Test) {
    // 0101101001 L = 5
    // 011011011111 L = 8
    // 10011100 L = 6
    EXPECT_EQ(lfsrcrypto::get_linear_complexity(""), 0);
}
