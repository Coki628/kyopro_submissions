#include "../base.hpp"

// 参考：http://sssiii.seesaa.net/upload/detail/image/affine_004.PNG.html
// アフィン行列の逆行列
template<typename T>
vector<vector<T>> affine_mat_inverse(const vector<vector<T>> &a) {
    auto res = a;
    res[0][0] *= -1;
    res[1][1] *= -1;
    return res;
}

