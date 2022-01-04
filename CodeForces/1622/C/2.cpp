/*
・自力AC！なんか噓っぽい気もするんだけど、通ったから正義。
・三分探索
・とりあえず最小のやつをある程度減らして、他をそいつの大きさに合わせるのがいいと思う。
　問題はそのある程度をどの程度にするかで、これは大きすぎても小さすぎても良くなさそう。
　凸っぽくなりそうということで、整数で(実験見る限り)同値が続くこともあるのに
　のに三分探索したくないなー…って思いながらも、
　他に手段も思いつかないのでやると、通った。前後100見た。
　判定パートで最悪O(N)使ってるけど、速度も0.1秒くらいで余裕だった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_dist/base.hpp"

#include "../../../_lib/cpp/_dist/macros.hpp"

#include "../../../_lib/cpp/_dist/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/template.hpp"

// 三分探索(整数)
template<typename F>
pll trisearch_min(ll lo, ll hi, const F &func, ll offset=1) {
    
    ll m1 = lo, l = lo;
    ll m2 = hi, r = hi;
    while (lo+2 < hi) {
        m1 = (lo*2+hi) / 3;
        m2 = (lo+hi*2) / 3;
        ll res1 = func(m1);
        ll res2 = func(m2);
        if (res1 <= res2) {
            hi = m2;
        } else {
            lo = m1;
        }
    }
    ll mn = INF;
    pll res;
    rep(i, max(m1-offset, l), min(m2+offset, r)) {
        ll val = func(i);
        if (val < mn) {
            mn = val;
            res = {i, val};
        }
    }
    return res;
}

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ll sm = sum(A);
    sort(ALL(A));
    auto check = [&](ll x) {
        ll a0 = A[0];
        ll cnt = 0;
        ll cursm = sm;
        if (cursm <= K) {
            return cnt;
        }
        ll need = cursm-K;
        if (need <= x) {
            cnt += need;
            return cnt;
        } else {
            a0 -= x;
            cursm -= x;
            cnt += x;
        }
        rep(i, N-1, 0, -1) {
            cursm -= abs(a0-A[i]);
            cnt++;
            if (cursm <= K) {
                return cnt;
            }
        }
        return INF;
    };
    auto [id, val] = trisearch_min(0, INF, check, 100);
    print(val);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
