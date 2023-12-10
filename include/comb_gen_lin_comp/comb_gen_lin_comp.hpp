#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace lfsrcrypto {
    size_t get_linear_complexity(const std::string_view& gamma);
    size_t get_linear_complexity_for_comb_gen(const std::vector<std::string_view>& regs_gamma,
                                            const std::function<size_t(const std::vector<size_t>&)>& func, bool par = false);
} // namespace lfsrcrypto
