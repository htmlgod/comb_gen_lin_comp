#pragma once

#include <functional>
#include <string>
#include <vector>

namespace lfsrcrypto {
    size_t get_linear_complexity(const std::string& gamma);
    size_t get_linear_complexity_for_comb_gen(const std::vector<std::string>& regs_gamma,
                                            const std::function<size_t(const std::vector<size_t>&)>& func, bool par = false);
    std::string gen_rand_gamma(size_t size);
} // namespace lfsrcrypto
