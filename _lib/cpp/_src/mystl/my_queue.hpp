#include "../base.hpp"

template<typename _Tp>
struct my_queue : queue<_Tp> {
    using queue<_Tp>::queue;
    _Tp pop() {
        _Tp res = this->front();
        queue<_Tp>::pop();
        return res;
    }
};
