#include "../base.hpp"

template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>>
struct my_multiset : public multiset<_Key, _Compare, _Alloc> {
    _Key front() {
        return *this->begin();
    }
    _Key pop_front() {
        auto res = this->front();
        this->erase(this->begin());
        return res;
    }
    _Key back() {
        return *this->rbegin();
    }
    _Key pop_back() {
        auto res = this->back();
        this->erase(prev(this->end()));
        return res;
    }
};
#define multiset my_multiset
