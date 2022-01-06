#include "../base.hpp"

// 参考：https://outline.hatenadiary.jp/entry/2020/07/02/205628
// 使い方
// ・行列累乗だとN^3logKかかるものをN^2logKで処理できる。
// ・制限として、当然どんな行列でも出来る訳じゃなくて、漸化式N本の行列累乗みたいのは無理で、
// 　N項間漸化式1本みたいな形の時だけできる。(多分)
// ・引数には最初のN-1項と、遷移の時に使うN-1項の係数を渡す。

// きたまさ法
template<typename T>
struct Kitamasa {
    vector<T> a;    // 初期値ベクトル
    vector<T> d;    // 係数ベクトル
    int k;
    
    Kitamasa(vector<T>& a, vector<T>& d) : a(a), d(d), k((int)a.size()) {}
    
    // a_n の係数ベクトルを求める
    vector<T> dfs(int64_t n) {
        if (n == k)  return d;
        
        vector<T> res(k);
        if (n & 1 || n < k * 2) {
            vector<T> x = dfs(n - 1);
            for (int i = 0; i < k; ++i)  res[i] = d[i] * x[k - 1];
            for (int i = 0; i + 1 < k; ++i)  res[i + 1] += x[i];
        }
        else {
            vector<vector<T>> x(k, vector<T>(k));
            x[0] = dfs(n >> 1);
            for (int i = 0; i + 1 < k; ++i) {
                for (int j = 0; j < k; ++j)  x[i + 1][j] = d[j] * x[i][k - 1];
                for (int j = 0; j + 1 < k; ++j)  x[i + 1][j + 1] += x[i][j];
            }
            for (int i = 0; i < k; ++i){
                for (int j = 0; j < k; ++j) {
                    res[j] += x[0][i] * x[i][j];
                }
            }
        }

        return res;
    }

    // a_n を求める
    T calc(int64_t n) {
        if (n < k) return a[n];
        vector<T> x = dfs(n);
        T res = 0;
        for (int i = 0; i < k; ++i)  res += x[i] * a[i];
        return res;
    }
};