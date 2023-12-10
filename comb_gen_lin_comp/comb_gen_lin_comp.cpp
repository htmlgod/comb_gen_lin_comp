#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

#include <thread>
#include <future>

#include <boost/dynamic_bitset.hpp>

namespace {
    bool is_power_of_2(size_t num) {
        return (num & (num - 1)) == 0;
    }
    size_t get_linear_complexity_cg(const std::string_view& gamma) {
        size_t L = 0;
        size_t m = gamma.size();

        std::string tmp = {gamma.begin(), gamma.end()};

        while (m > 1) {
            m /= 2;
            auto l = tmp.substr(0, m);
            auto r = tmp.substr(m, 2*m);
            boost::dynamic_bitset<> b = boost::dynamic_bitset<>(l) ^ boost::dynamic_bitset<>(r);
            if (b.none()) {
                tmp = l;
            }
            else {
                L += m;
                boost::to_string(b,tmp);
            }
        }
        if (tmp[0] == '1')
            L += 1;
        return L;
    }
    size_t get_linear_complexity_bm(const std::string_view& gamma) {
        return 0;
    }
    size_t get_linear_complexity_for_comb_gen_nonpar(const std::vector<std::string_view>& regs_gamma,
                                                     const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<size_t> reg_comps;
        reg_comps.reserve(regs_gamma.size());
        for (const auto& gamma : regs_gamma)
            reg_comps.push_back(lfsrcrypto::get_linear_complexity(gamma));
        return func(reg_comps);
    }
    size_t get_linear_complexity_for_comb_gen_par(const std::vector<std::string_view>& regs_gamma,
                                                  const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<std::future<size_t>> futures;
        futures.reserve(regs_gamma.size());
        for (auto&& gamma : regs_gamma)
            futures.push_back(std::async(std::launch::async, &lfsrcrypto::get_linear_complexity, std::move(gamma)));
        
        std::vector<size_t> reg_comps;
        reg_comps.reserve(regs_gamma.size());
        for (auto& future : futures)
            reg_comps.push_back(future.get());

        return func(reg_comps);
    }
}

namespace lfsrcrypto {

    size_t get_linear_complexity(const std::string_view& gamma) {
        if (is_power_of_2(gamma.size()))
            return get_linear_complexity_cg(gamma);
        else
            return get_linear_complexity_bm(gamma);
    }

    size_t get_linear_complexity_for_comb_gen(const std::vector<std::string_view>& regs_gamma,
            const std::function<size_t(const std::vector<size_t>&)>& func, bool par) {
        if (par)
            return get_linear_complexity_for_comb_gen_par(regs_gamma, func);
        else
            return get_linear_complexity_for_comb_gen_nonpar(regs_gamma, func);
    }

} // namespace lfsrcrypto
