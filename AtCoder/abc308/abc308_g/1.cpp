/*
・upsolveした。
・XORの性質
・実はソート済を隣接だけ見れば最小値が取れる。
　いやー、気付かないよこういうの。
・それが分かれば、あとはsetやらmapやら使って適切にやればOK。
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
    map<ll, ll> C;
    multiset<ll> se;
    ll dupcnt = 0;
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            C[x]++;
            if (C[x] == 2) {
                dupcnt++;
            }
            if (C[x] == 1) {
                auto itr = C.find(x);
                if (itr != C.begin()) {
                    ll y = prev(itr)->first;
                    se.insert(x ^ y);
                }
                if (next(itr) != C.end()) {
                    ll y = next(itr)->first;
                    se.insert(x ^ y);
                }
                if (itr != C.begin() and next(itr) != C.end()) {
                    ll y = prev(itr)->first;
                    ll z = next(itr)->first;
                    se.erase(se.find(y ^ z));
                }
            }
        } else if (op == 2) {
            ll x;
            cin >> x;
            C[x]--;
            if (C[x] == 1) {
                dupcnt--;
            }
            if (C[x] == 0) {
                auto itr = C.find(x);
                if (itr != C.begin()) {
                    ll y = prev(itr)->first;
                    se.erase(se.find(x ^ y));
                }
                if (next(itr) != C.end()) {
                    ll y = next(itr)->first;
                    se.erase(se.find(x ^ y));
                }
                if (itr != C.begin() and next(itr) != C.end()) {
                    ll y = prev(itr)->first;
                    ll z = next(itr)->first;
                    se.insert(y ^ z);
                }
                C.erase(x);
            }
        } else if (op == 3) {
            ll res = dupcnt ? 0 : *se.begin();
            print(res);
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
