/*
・ブザービートで通した…！
・状態がN*2しかなさそう。けどこの順列全部陽に持つとN*Nになって無理なので、
　連続した値の(先頭,末尾)みたいなペアにして持って、これでBFSやる。
・途中までの考え方はよかったけど、データの持ち方が悪すぎた。
　おかげで更新時の場合分けが大変なことに…。
　結局、昇順向きか降順向きどっちかと、シフトの位置くらいしか持たなくていいみたい。
　ちょっとそう思ったんだけど、なんか実験やった時に山なりみたいな列を見た気がして、
　だったらもっと正確に持った方がいいなって今の形になったんだよね。。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N;
    cin >> N;
    deque<pll> cur = {{0, N-1}};
    map<deque<pll>, ll> memo;
    memo[cur] = 0;
    queue<deque<pll>> que;
    que.push(cur);
    while (que.size()) {
        auto cur = que.front(); que.pop();
        auto nxt = cur;
        reverse(ALL(nxt));
        for (auto& p : nxt) {
            swap(p.first, p.second);
        }
        if (not memo.count(nxt)) {
            memo[nxt] = memo[cur]+1;
            que.push(nxt);
        }

        nxt = cur;
        auto tmp = nxt.back().second;
        if (nxt.back().first < nxt.back().second) {
            nxt.back().second--;
        } elif (nxt.back().first > nxt.back().second) {
            nxt.back().second++;
        } else {
            nxt.pop_back();
        }
        if (nxt.front().first < nxt.front().second) {
            if (tmp+1 == nxt.front().first) {
                nxt.front().first--;
            } else {
                nxt.push_front({tmp, tmp});
            }
        } elif (nxt.front().first > nxt.front().second) {
            if (tmp-1 == nxt.front().first) {
                nxt.front().first++;
            } else {
                nxt.push_front({tmp, tmp});
            }
        } else {
            if (tmp+1 == nxt.front().first) {
                nxt.front().first--;
            } elif (tmp-1 == nxt.front().first) {
                nxt.front().first++;
            } else {
                nxt.push_front({tmp, tmp});
            }
        }
        if (not memo.count(nxt)) {
            memo[nxt] = memo[cur]+1;
            que.push(nxt);
        }
    }
    // for (auto [dq, dist] : memo) {
    //     rep(i, dq.size()) {
    //         print(dq[i]);
    //     }
    //     debug(dist);
    // }

    auto A = LIST(N);
    rep(i, N) A[i]--;
    deque<pll> dq;
    ll x = A[0];
    rep(i, N-1) {
        if (A[i]+1 == A[i+1]) {
        } elif (A[i]-1 == A[i+1]) {
        } else {
            dq.eb(x, A[i]);
            x = A[i+1];
        }
    }
    dq.eb(x, A[N-1]);
    ll ans = memo[dq];
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}
