/*
参考：https://twitter.com/kude_coder/status/1475510773611130880
　　　https://twitter.com/mkawa2/status/1475508422179430400
・割と近い方針を引いていたが詰め切れず。引くのは「被ってる区間長」だった。。
・数え上げ、区間
・1をK個含む、めいっぱい引き延ばした区間毎に数える。
　その中で自由にシャッフルしたものをnCr(区間長, K)でまず数える。
　2つ目以降の区間では前回の区間と被ってない部分を固定するとすると、
　被ってる部分を自由にシャッフルした分は重複(のはず)なので、nCr(被ってる区間長, K-1)を引く。
・「めいっぱい引き延ばした区間」が尺取りなら地味に面倒そうだけどN^2がOKなので愚直っぽくやる。
・あーでもBITにぶたんにすればそんな大変じゃないかもな。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_dist/base.hpp"

#include "../../../_lib/cpp/_dist/macros.hpp"

#include "../../../_lib/cpp/_dist/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    vector<ll> A(N);
    rep(i, N) {
        A[i] = toint(S[i]);
    }

    ll sm = sum(A);
    if (K == 0 or sm < K) {
        print(1);
        return;
    }

    ModTools<mint> mt(N);
    mint ans = 0;
    bool first = true;
    ll prvr = -1;
    rep(i, N) {
        if (A[i] == 1) {
            ll cnt = 1;
            ll l = i;
            while (l-1 >= 0 and A[l-1] == 0) {
                l--;
            }
            ll r = i+1;
            while (r < N and cnt+A[r] <= K) {
                cnt += A[r];
                r++;
            }
            ll len = r-l;
            if (first) {
                ans += mt.nCr(len, K);
                first = false;
            } else {
                ll dup = prvr-l;
                ans += mt.nCr(len, K)-mt.nCr(dup, K-1);
            }
            if (r == N) break;
            prvr = r;
        }
    }
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
