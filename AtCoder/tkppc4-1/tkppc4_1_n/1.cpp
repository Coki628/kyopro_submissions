/*
・dojo set_e_5_g
・なんとか自力AC！
・素因数分解、尺取り、zero sum ranges系
・積の方を考えると単調性が使える。和の方を考えるとmod Dでzero sum rangesみたいにできる。
　合わせると、左端を決めると、積で使える右端が区間になるので、
　その区間内で、左端位置の値と和でペアになれるような個数を数える。
　なんか普通にmapでやろうとすると、右端固定でそこより手前で左端になれる個数みたいになって
　今回の左端固定で右端を区間にする形とマッチしないので、WM持ち出してrange_freqで殴った。
　積を管理する素因数分解の尺取りみたいなやつが結構バグって大変だった…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N, D;
    cin >> N >> D;
    auto A = LIST(N);

    vector<ll> acc(N);
    acc[0] = A[0] % D;
    rep(i, 1, N) {
        acc[i] = (acc[i-1]+A[i]) % D;
    }
    acc.insert(acc.begin(), 0);
    WaveletMatrix<ll, 32> wm(acc);

    vector<vector<pli>> fact(N);
    rep(i, N) {
        fact[i] = factorize(A[i]);
    }
    ll r = 0, ans = 0;
    map<ll, ll> cur;
    auto dfact = factorize(D);
    auto check = [&]() {
        for (auto [k, v] : dfact) {
            if (cur[k] < v) {
                return false;
            }
        }
        return true;
    };
    bool ok = false;
    rep(l, N) {
        while (l >= r or (r < N and not ok)) {
            for (auto [k, v] : fact[r]) {
                cur[k] += v;
            }
            ok = check();
            r++;
        }
        if (ok) {
            ans += wm.range_freq(r, N+1, acc[l], acc[l]+1);
        }
        for (auto [k, v] : fact[l]) {
            cur[k] -= v;
        }
        ok = check();
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
