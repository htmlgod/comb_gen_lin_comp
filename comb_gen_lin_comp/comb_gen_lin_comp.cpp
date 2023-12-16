#include <comb_gen_lin_comp/comb_gen_lin_comp.hpp>

#include <cmath>
#include <future>
#include <random>
#include <thread>
#include <mutex>

#include <omp.h>

#include <boost/dynamic_bitset.hpp>

namespace {
    bool is_power_of_2(size_t num) {
        return (num & (num - 1)) == 0; // http://www.graphics.stanford.edu/~seander/bithacks.html#DetermineIfPowerOf2
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
    size_t get_linear_complexity_for_comb_gen_seq(const std::vector<std::string>& regs_gamma,
                                                  const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<size_t> reg_comps;
        reg_comps.reserve(regs_gamma.size());
        for (const auto& gamma : regs_gamma)
            reg_comps.push_back(lfsrcrypto::get_linear_complexity(gamma));
        return func(reg_comps);
    }
    size_t get_linear_complexity_for_comb_gen_openmp(const std::vector<std::string>& regs_gamma,
                                                     const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<size_t> reg_comps;
        reg_comps.resize(regs_gamma.size());
        #pragma omp parallel num_threads(regs_gamma.size()) shared(regs_gamma, reg_comps)
        {
            int i = omp_get_thread_num();
            reg_comps[i] = lfsrcrypto::get_linear_complexity(regs_gamma[i]);
        }
        return func(reg_comps);
    }
    size_t get_linear_complexity_for_comb_gen_threads(const std::vector<std::string>& regs_gamma,
                                                      const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<size_t> reg_comps;
        std::vector<std::thread> threads;
        std::mutex m1;
        for (const auto& gamma : regs_gamma)
            threads.emplace_back(std::thread([&m1, &reg_comps, &gamma](){
                auto res = lfsrcrypto::get_linear_complexity(gamma);
                std::lock_guard<std::mutex> l(m1);
                reg_comps.push_back(res);
            }));
        for (auto&& t : threads)
            t.join();
        return func(reg_comps);
    }
    size_t get_linear_complexity_for_comb_gen_async(const std::vector<std::string>& regs_gamma,
                                                    const std::function<size_t(const std::vector<size_t>&)>& func) {
        std::vector<std::future<size_t>> futures;
        futures.reserve(regs_gamma.size());
        for (auto& gamma : regs_gamma)
            futures.push_back(
                    std::async(std::launch::async, &lfsrcrypto::get_linear_complexity, std::move(gamma)));

        std::vector<size_t> reg_comps;
        reg_comps.reserve(regs_gamma.size());
        for (auto&& future : futures)
            reg_comps.push_back(future.get());
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
            const std::function<size_t(const std::vector<size_t>&)>& func, EXEC_TYPE exec_t) {
        size_t result;
        switch(exec_t) {
            case EXEC_TYPE::SEQ:
                result = get_linear_complexity_for_comb_gen_seq(regs_gamma, func);
                break;
            case EXEC_TYPE::THREADS:
                result = get_linear_complexity_for_comb_gen_threads(regs_gamma, func);
                break;
            case EXEC_TYPE::ASYNC:
                result = get_linear_complexity_for_comb_gen_async(regs_gamma, func);
                break;
            case EXEC_TYPE::OPENMP:
                result = get_linear_complexity_for_comb_gen_openmp(regs_gamma, func);
                break;
        }
        return result;
    }

    std::string gen_rand_gamma(size_t size) {
        static std::random_device rd;
        std::mt19937_64 mt(rd());
        size_t block_size = 64;
        size_t num_of_blocks = size / block_size + (size % block_size > 0 ? 1 : 0);
        auto lower_bound = std::pow(2, block_size/2);
        auto upper_bound = std::pow(2, block_size) - 1;
        std::uniform_int_distribution<uint64_t> uniform_dist(lower_bound, upper_bound);

        std::string out;
        for (size_t i = 0; i < num_of_blocks; ++i) {
            std::string tmp;
            boost::to_string(boost::dynamic_bitset<>(size, uniform_dist(mt)), tmp);
            out += tmp;
        }
        return out;
    }

} // namespace lfsrcrypto
