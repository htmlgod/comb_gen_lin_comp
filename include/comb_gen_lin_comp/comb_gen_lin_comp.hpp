#pragma once

#include <functional>
#include <string>
#include <vector>

namespace lfsrcrypto {
    enum class EXEC_TYPE {
        SEQ,
        THREADS,
        ASYNC,
        OPENMP
    };
    size_t get_linear_complexity(const std::string& gamma);
    size_t get_linear_complexity_for_comb_gen(const std::vector<std::string>& regs_gamma,
                                            const std::function<size_t(const std::vector<size_t>&)>& func, EXEC_TYPE exec_t = EXEC_TYPE::SEQ);
    std::string gen_rand_gamma(size_t size);
} // namespace lfsrcrypto
