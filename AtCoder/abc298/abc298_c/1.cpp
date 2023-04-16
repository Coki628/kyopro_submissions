/*
・きっちり自力AC！
・index毎にpqとsetに詰めとく。
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
    ll N, Q;
    cin >> N >> Q;
    vector<priority_queue<ll, vector<ll>, greater<ll>>> A(N);
    map<ll, set<ll>> B;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll i, j;
            cin >> i >> j;
            j--;
            A[j].push(i);
            B[i].insert(j + 1);
        } else if (op == 2) {
            ll i;
            cin >> i;
            i--;
            auto tmp = A[i];
            vector<ll> res;
            while (A[i].size()) {
                res.eb(A[i].top());
                A[i].pop();
            }
            print(res);
            A[i] = tmp;
        } else if (op == 3) {
            ll i;
            cin >> i;
            print(B[i]);
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
