#include "../base.hpp"
#include "../common/print.hpp"

template<typename _Tp>
struct my_deque : deque<_Tp> {
    using deque<_Tp>::deque;
    _Tp pop_front() {
        _Tp res = this->front();
        deque<_Tp>::pop_front();
        return res;
    }
    _Tp pop_back() {
        _Tp res = this->back();
        deque<_Tp>::pop_back();
        return res;
    }
};

template<typename T>
void print(const my_deque<T> &que) {
    vector<T> V(que.begin(), que.end());
    print(V);
}
