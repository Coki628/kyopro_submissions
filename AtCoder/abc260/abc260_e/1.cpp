/*
・終了後自力AC？
・尺取り、いもす
・TLでキーワードは拾ってしまったけど、本番中も尺取りって感づいたし、
　こっち取り組んでたらワンチャンあったかもしれないな…。
　その時はなんか結構めんどくさい尺取りかと思ったんだけど、
　やってみたらそこまでめんどくなかった。。
・ある区間が条件を満たした時、そこより広く取った場所も全部満たすタイプの尺取り。
　よって右端を動かして条件満たしたら、そこより先の右端も全部足し込む。
　今回は答えが総和とかではなく区間長毎に取らないといけないので、
　ある区間長から、その先右端まで伸ばすといくつ長くなった所までいけるかで、
　いもすみたいに区間の開始と終了で足し引きしておく。最後に累積和取る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
    }

    vvl adj(M);
    rep(i, N) {
        adj[A[i]].eb(i);
        adj[B[i]].eb(i);
    }
    vector<ll> ans(M+2), C(N);
    ll sz = 0, r = 0;
    rep(l, M) {
        while (r < M and sz < N) {
            for (auto i : adj[r]) {
                if (C[i] == 0) sz++;
                C[i]++;
            }
            r++;
        }
        if (sz == N) {
            ll len = r - l;
            ans[len]++;
            ans[len+(M-r)+1]--;
        }
        assert(l < r);
        vector<ll> erase;
        for (auto i : adj[l]) {
            C[i]--;
            if (C[i] == 0) sz--;
        }
    }
    rep(i, 1, M+1) {
        ans[i+1] += ans[i];
    }
    print(subarray(ans, 1, M+1));
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
