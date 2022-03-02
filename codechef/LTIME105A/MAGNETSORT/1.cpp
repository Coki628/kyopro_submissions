/*
・きっちり自力AC！
・SNかNSで区間をめいっぱい長くするのが最善。
　自明OKと自明NGを弾いた後、1手でできるか2手かかるかをチェック。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    string S;
    cin >> S;

    if (sorted(A) == A) {
        print(0);
        return;
    }
    if (count(ALL(S), 'S') == N or count(ALL(S), 'N') == N) {
        print(-1);
        return;
    }

    ll l1 = INF, l2 = INF, r1 = -INF, r2 = -INF;
    rep(i, N) {
        if (S[i] == 'S') {
            l1 = i;
            break;
        }
    }
    rep(i, N) {
        if (S[i] == 'N') {
            l2 = i;
            break;
        }
    }
    rep(i, N-1, -1, -1) {
        if (S[i] == 'N') {
            r1 = i+1;
            break;
        }
    }
    rep(i, N-1, -1, -1) {
        if (S[i] == 'S') {
            r2 = i+1;
            break;
        }
    }
    if (l1 < r1) {
        auto tmp = A;
        sort(tmp.begin()+l1, tmp.begin()+r1);
        if (tmp == sorted(A)) {
            print(1);
            return;
        }
    }
    if (l2 < r2) {
        auto tmp = A;
        sort(tmp.begin()+l2, tmp.begin()+r2);
        if (tmp == sorted(A)) {
            print(1);
            return;
        }
    }
    print(2);
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
