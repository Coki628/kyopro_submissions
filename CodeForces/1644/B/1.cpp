/*
・きっちり自力AC！
・なんか大概うまくいきそうじゃん、を信じて乱択。
　制約も小さいので、判定は愚直でOKだし、答えの列はsetに陽に詰めれる。
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

#include "common/randrange.hpp"

void solve() {
    ll N;
    cin >> N;

    auto check = [&](const vector<ll>& P) -> bool {
        rep(i, 2, N) {
            if (P[i-2]+P[i-1] == P[i]) {
                return false;
            }
        }
        return true;
    };

    vector<ll> P(N);
    iota(ALL(P), 1);
    reverse(ALL(P));
    set<vector<ll>> ok, ng;
    while (ok.size() < N) {
        while (ok.count(P) or ng.count(P)) {
            ll i = randrange(0, N);
            ll j = i;
            while (j == i) {
                j = randrange(0, N);
            }
            swap(P[i], P[j]);
        }
        if (check(P)) {
            ok.insert(P);
        } else {
            ng.insert(P);
        }
    }
    for (auto& v : ok) print(v);
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
