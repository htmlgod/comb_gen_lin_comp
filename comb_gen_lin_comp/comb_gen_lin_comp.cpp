#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

#include <cmath>
#include <future>
#include <random>
#include <thread>
#include <mutex>
#include <iostream>

#include <boost/dynamic_bitset.hpp>

namespace {
    bool is_power_of_2(size_t num) {
        return (num & (num - 1)) == 0;
    }
    size_t get_linear_complexity_cg(const std::string& gamma) {
        size_t L = 0;
        size_t m = gamma.size();

        auto tmp = gamma;

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
    size_t get_linear_complexity_bm(const std::string& gamma) {
        return 0;
    }
    size_t get_linear_complexity_for_comb_gen_nonpar(const std::vector<std::string>& regs_gamma,
                                                     const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<size_t> reg_comps;
        reg_comps.reserve(regs_gamma.size());
        for (const auto& gamma : regs_gamma)
            reg_comps.push_back(lfsrcrypto::get_linear_complexity(gamma));
        return func(reg_comps);
    }
    size_t get_linear_complexity_for_comb_gen_par(const std::vector<std::string>& regs_gamma,
                                                  const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<std::future<size_t>> futures;
        //futures.reserve(regs_gamma.size());
        for (auto& gamma : regs_gamma)
            futures.push_back(std::async(std::launch::async, &lfsrcrypto::get_linear_complexity, std::move(gamma)));

        std::vector<size_t> reg_comps;
        //reg_comps.reserve(regs_gamma.size());
        for (auto&& future : futures)
            reg_comps.push_back(future.get());

        //std::vector<size_t> reg_comps;
        //std::vector<std::thread> threads;
        //std::mutex m1;
        //for (const auto& gamma : regs_gamma)
        //    threads.emplace_back(std::thread([&m1, &reg_comps, &gamma](){
        //        auto res = lfsrcrypto::get_linear_complexity(gamma);
        //        std::lock_guard<std::mutex> l(m1);
        //        reg_comps.push_back(res);
        //    }));
        //for (auto&& t : threads)
        //    t.join();

        return func(reg_comps);
    }
}

namespace lfsrcrypto {
    size_t get_linear_complexity(const std::string& gamma) {
        if (is_power_of_2(gamma.size()))
            return get_linear_complexity_cg(gamma);
        else
            return get_linear_complexity_bm(gamma);
    }

    size_t get_linear_complexity_for_comb_gen(const std::vector<std::string>& regs_gamma,
            const std::function<size_t(const std::vector<size_t>&)>& func, bool par) {
        if (par)
            return get_linear_complexity_for_comb_gen_par(regs_gamma, func);
        else
            return get_linear_complexity_for_comb_gen_nonpar(regs_gamma, func);
    }

    std::string gen_rand_gamma(size_t size) {
        static std::random_device rd;
        std::mt19937_64 mt(rd());
        if (size > 64)
            size = 64;
        auto lower_bound = std::pow(2, size/2);
        auto upper_bound = std::pow(2, size) - 1;
        std::uniform_int_distribution<uint64_t> uniform_dist(lower_bound, upper_bound);

        std::string out;
        boost::to_string(boost::dynamic_bitset<>(size, uniform_dist(mt)), out);
        if (size > 64) {
            std::string tmp;
            boost::to_string(boost::dynamic_bitset<>(size, uniform_dist(mt)), tmp);
            out += tmp;
        }
        return out;
    }

} // namespace lfsrcrypto
