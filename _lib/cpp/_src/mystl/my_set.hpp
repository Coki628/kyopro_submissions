#include "../base.hpp"
#include "../common/print.hpp"

template<typename _Key>
struct my_set : set<_Key> {
    using set<_Key>::set;
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
void print(const my_set<T> &se) {
    vector<T> V(se.begin(), se.end());
    print(V);
}
