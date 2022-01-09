#include "../base.hpp"
#include "../common/print.hpp"

template<typename _Key>
struct my_multiset : multiset<_Key> {
    using multiset<_Key>::multiset;
    _Key front() {
        return *this->begin();
    }
    _Key pop_front() {
        _Key res = this->front();
        this->erase(this->begin());
        return res;
    }
    _Key back() {
        return *this->rbegin();
    }
    _Key pop_back() {
        _Key res = this->back();
        this->erase(prev(this->end()));
        return res;
    }
};

template<typename T>
void print(const multiset<T> &se) {
    vector<T> V(se.begin(), se.end());
    print(V);
}
