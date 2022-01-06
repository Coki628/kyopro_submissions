#include "../macros.hpp"

// スライド最小値(比較関数、元の数列、遷移回数、遷移幅、遷移の重み)
template<typename T, typename F>
vector<T> slide_min(const F &func, vector<T> &A, ll k, ll w=1, ll v=0) {

    ll N = A.size();
    auto res = A;
    rep(a, w) {
        deque<pair<int, T>> que;
        int i = 0;
        while (i*w+a < N) {
            ll val = A[i*w+a] - i*v;
            while (!que.empty() and func(que.back().second, val) == val) {
                que.pop_back();
            }
            que.pb({i, val});
            res[i*w+a] = que.front().second + i*v;
            if (que.front().first == i-k+1) {
                que.pop_front();
            }
            i++;
        }
    }
    return res;
}
