#include "../base.hpp"

template<typename _Tp, typename _Sequence=deque<_Tp>>
struct my_queue : public queue<_Tp, _Sequence> {
    _Tp pop() {
        auto res = this->front();
        queue<_Tp, _Sequence>::pop();
        return res;
    }
};
#define queue my_queue
