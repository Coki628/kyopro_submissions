#include "../base.hpp"

// 標準mapを継承したdefaultdict
template<typename _Key, typename _Tp>
struct defaultdict : map<_Key, _Tp> {
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
