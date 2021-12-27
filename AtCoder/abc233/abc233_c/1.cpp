/*
・きっちり自力AC！
・再帰全探索
・制約をよく検討すると、実は状態は少ない。
　不規則な個数から選び出すやつなので、再帰全探索で書いた。
　掛け算のオーバーフローで1ペナ。。
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
    ll N, X;
    cin >> N >> X;
    vvl A(N);
    vector<ll> M(N);
    rep(i, N) {
        cin >> M[i];
        A[i] = LIST(M[i]);
    }

    ll cur = 1, ans = 0;
    auto rec = [&](auto&& f, ll i) {
        if (i == N) {
            if (cur == X) ans++;
            return;
        }
        rep(j, M[i]) {
            if (not mul_overflow(cur, A[i][j])) {
                cur *= A[i][j];
                f(f, i+1);
                cur /= A[i][j];
            }
        }
    };
    rec(rec, 0);
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
