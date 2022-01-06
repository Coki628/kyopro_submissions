#include "../base.hpp"

template<typename _Tp, typename _Alloc=std::allocator<_Tp>>
struct my_deque : public deque<_Tp, _Alloc> {
    _Tp pop_front() {
        auto res = this->front();
        deque<_Tp, _Alloc>::pop_front();
        return res;
    }
    _Tp pop_back() {
        auto res = this->back();
        deque<_Tp, _Alloc>::pop_back();
        return res;
    }
};
#define deque my_deque
