#include "../base.hpp"

template<typename T> vector<vector<T>> list2d(int N, int M, T init) {
    return vector<vector<T>>(N, vector<T>(M, init));
}

template<typename T> vector<vector<vector<T>>> list3d(int N, int M, int L, T init) {
    return vector<vector<vector<T>>>(N, vector<vector<T>>(M, vector<T>(L, init)));
}

template<typename T> vector<vector<vector<vector<T>>>> list4d(int N, int M, int L, int O, T init) {
    return vector<vector<vector<vector<T>>>>(N, vector<vector<vector<T>>>(M, vector<vector<T>>(L, vector<T>(O, init))));
}
