/*
・upsolveした。
・BIT26本
・本番終了後のことをなんとなく覚えてたけど、それでもまあまあ実装は面倒だった。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;
    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - 'a';
    }
    ll Q;
    cin >> Q;
    ll M = 26;
    vector<BIT<ll>> bit(M, BIT<ll>{N});
    rep(i, N) {
        bit[A[i]].add(i, 1);
    }
    auto C = Counter(A);

    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            char c;
            cin >> x >> c;
            x--;
            c -= 'a';
            bit[A[x]].add(x, -1);
            bit[c].add(x, 1);
            C[A[x]]--;
            C[c]++;
            A[x] = c;
        } else {
            ll l, r;
            cin >> l >> r;
            l--;

            vector<pll> vec;
            ll i = l;
            bool started = false;
            rep(c, M) {
                ll j = bisearch_max(i, r + 1, [&](ll x) {
                    return bit[c].query(i, x) == x - i;
                });
                if (started or j > i) {
                    started = true;
                    vec.eb(c, j - i);
                }
                i = j;
                if (i == r) break;
            }
            bool ok = true;
            // ソート済か
            if (i == r) {
                ll n = vec.size();
                assert(n >= 1);
                rep(j, n) {
                    if (j == 0 or j == n - 1) continue;
                    auto [k, v] = vec[j];
                    // 左右端以外の文字の個数が合ってるか
                    if (C[k] != v) {
                        ok = false;
                        break;
                    }
                }
            } else {
                ok = false;
            }
            if (ok) {
                Yes();
            } else {
                No();
            }
        }
    }
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
