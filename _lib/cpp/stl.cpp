/*
・ライブラリ：STLカスタマイズ
*/

#include "_tpl.cpp"


// 標準mapを継承したdefaultdict
template <typename _Key, typename _Tp, typename _Compare=less<_Key>, typename _Alloc=allocator<pair<const _Key, _Tp>>>
struct defaultdict : public map<_Key, _Tp, _Compare, _Alloc> {

    const _Tp init;

    defaultdict() : init(_Tp()) {};

    defaultdict(_Tp init) : init(init) {}

    _Tp& operator[](const _Key& k) {
        if (this->count(k)) {
            return map<_Key, _Tp>::operator[](k);
        } else {
            return map<_Key, _Tp>::operator[](k) = init;
        }
    }

    _Tp& operator[](_Key&& k) {
        if (this->count(k)) {
            return map<_Key, _Tp>::operator[](k);
        } else {
            return map<_Key, _Tp>::operator[](k) = init;
        }
    }
};


template<typename _Key, typename _Compare=less<_Key>, typename _Alloc=allocator<_Key>>
struct my_set : public set<_Key, _Compare, _Alloc> {
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


template<typename _Tp, typename _Sequence=vector<_Tp>, typename _Compare=less<typename _Sequence::value_type>>
struct my_priority_queue : public priority_queue<_Tp, _Sequence, _Compare> {
    _Tp pop() {
        auto res = this->top();
        priority_queue<_Tp, _Sequence, _Compare>::pop();
        return res;
    }
};
#define priority_queue my_priority_queue


template<typename _Tp, typename _Sequence=deque<_Tp>>
struct my_queue : public queue<_Tp, _Sequence> {
    _Tp pop() {
        auto res = this->front();
        queue<_Tp, _Sequence>::pop();
        return res;
    }
};
#define queue my_queue


template<typename _Tp, typename _Sequence=deque<_Tp>>
struct my_stack : public stack<_Tp, _Sequence> {
    _Tp pop() {
        auto res = this->top();
        stack<_Tp, _Sequence>::pop();
        return res;
    }
};
#define stack my_stack


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


template<typename _Tp, typename _Alloc=std::allocator<_Tp>>
struct my_vector : public vector<_Tp, _Alloc> {
    _Tp pop() {
        auto res = this->back();
        this->pop_back();
        return res;
    }
};
#define vector my_vector
