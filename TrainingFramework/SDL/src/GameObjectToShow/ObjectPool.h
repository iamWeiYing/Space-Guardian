#ifndef __POOL_HPP
#define __POOL_HPP
#include <array>
#include <memory>
#include <bitset>
#include <stdexcept>
#include <string>

template <class T, size_t N>
class Pool {
public:
    using const_iterator = typename std::array<T, N>::const_iterator;

    template<class ...Args>
    Pool(Args&& ...args)
        :num_of_avail_(N), storage_{}, status_{}
    {
        storage_.fill(T{ std::forward<Args>(args)... });
        status_.set();
    }

    template<class Iterator>
    Pool(Iterator begin, Iterator end)
        :num_of_avail_(N), storage_{}, status_{}
    {
        if (N != std::distance(begin, end))
            throw std::runtime_error("distance between begin and end isn't:" + std::to_string(N));

        std::move(begin, end, storage_.begin());
        status_.set();
    }

    Pool(std::initializer_list<T> init)
        :num_of_avail_{ N }, storage_{}, status_{}
    {
        if (init.size() != N)
            throw std::runtime_error("mismatch size of initializer_list and pool");
        std::copy(init.begin(), init.end(), storage_.begin());
        status_.set();
    }

    Pool(const Pool& other) = delete;
    Pool(Pool&& other) = delete;
    Pool& operator = (const Pool& other) = delete;
    Pool& operator = (Pool&& other) = delete;

    auto acquire() noexcept
    {
        auto deleter = [this](const T* obj) {
            if (nullptr != obj) {
                status_.set(obj - &storage_[0]);
                ++num_of_avail_;
            }
        };

        if (0 == num_of_avail_)
            return std::unique_ptr<T, decltype(deleter)>(nullptr, deleter);

        for (size_t i = 0; i < status_.size(); ++i) {
            if (status_[i]) {
                status_.reset(i);
                --num_of_avail_;
                return std::unique_ptr<T, decltype(deleter)>(&storage_[i], deleter);
            }
        }

        return std::unique_ptr<T, decltype(deleter)>(nullptr, deleter);
    }

    size_t num_of_avail() const noexcept { return num_of_avail_; }

    const_iterator begin() const noexcept { return storage_.cbegin(); }

    const_iterator end() const noexcept { return storage_.cend(); }
private:
    size_t num_of_avail_;
    std::array<T, N> storage_;
    std::bitset<N> status_;
};

#endif
