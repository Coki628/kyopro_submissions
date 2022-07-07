/*
・JOI埋め
・なんとか自力AC！
・周期
・まず偶奇だけ分かればいいのでmod 2で考える。
　M<=24なので、24ビットの整数値として扱う。
　この整数値を1つの項とすると、最大でも2^24までの項で周期を作るはずだけど、
　実験してみると、周期になる時は最初の値に(多分確実に)戻ることが分かるので、
　始めの端数を考えなくてよくて少し楽になる。
　区間和[p,q]を求めるので、f(p)-f(q-1)みたいにする。
　Aが全部偶数だったら自明にずっと0なので別処理。
　メモリが64MBでつらめなので、訪問済配列をintではなくboolにする。
　(始めに戻るとは限らなかったらどうするんだろ)
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
    ll M, p, q;
    cin >> M >> p >> q;
    p--; q--;
    auto A = LIST(M);

    auto f = [&](ll x) -> ll {
        ll init = 0, res = 0;
        rep(i, M) {
            if (A[i]%2 == 1) {
                init |= 1LL<<i;
                res++;
            }
            if (i == x) {
                return res;
            }
        }
        x -= M - 1;

        if (popcount(init) == 0) {
            return 0;
        }

        // vector<int> visited(1LL<<M, -1);
        vector<bool> visited(1LL<<M);
        ll cur = init;
        visited[cur] = true;
        ll oddcnt = 0, cyclelen = -1;
        rep(i, 1LL<<M) {
            ll nxb = (cur>>0 & 1) ^ (cur>>(M-1) & 1);
            assert(nxb == 0 or nxb == 1);
            ll nxt = (nxb<<(M-1)) | (cur>>1);
            if (nxb == 1) oddcnt++;
            if (visited[nxt]) {
                // assert(visited[nxt] == 0);
                cyclelen = i + 1;
                break;
            }
            visited[nxt] = true;
            cur = nxt;
        }
        assert(cyclelen != -1);

        auto [d, m] = divmod(x, cyclelen);
        res += oddcnt * d;
        cur = init;
        rep(i, m) {
            ll nxb = (cur>>0 & 1) ^ (cur>>(M-1) & 1);
            assert(nxb == 0 or nxb == 1);
            ll nxt = (nxb<<(M-1)) | (cur>>1);
            if (nxb == 1) res++;
            cur = nxt;
        }
        return res;
    };

    ll ans = f(q);
    if (p) ans -= f(p-1);
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
