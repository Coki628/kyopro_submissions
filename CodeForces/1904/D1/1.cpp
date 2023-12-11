/*
参考：https://twitter.com/kude_coder/status/1733555823727743004
・自力ならず。。
・基本方針は、
　・左右に向かってB[i]と等しいA[j]を探しに行く
　・途中で跨げない場所があったら取りに行けない
　・全部適切に持ってこれればOK
　といったもので、この「跨げない場所」の条件2つのうち、
　「目的の値B[i]より大きいA[j]は無理」の方が詰め切れず終了。
　この条件だけ足したらちゃんと通った…。
・こういうの見つからない時どうしたらいいかねー。
　やっぱ地道に愚直コードとランダムケース書くしかないかー。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    rep(i, N) {
        if (A[i] > B[i]) {
            NO();
            return;
        }
    }
    rep(i, N) {
        if (A[i] == B[i]) continue;
        bool ok = false;
        rep(j, i + 1, N) {
            // ↓この条件が見つけられなかった
            if (A[j] > B[i]) break;
            if (B[j] < B[i]) break;
            if (A[j] == B[i]) {
                ok = true;
                break;
            }
        }
        rep(j, i - 1, -1, -1) {
            if (A[j] > B[i]) break;
            if (B[j] < B[i]) break;
            if (A[j] == B[i]) {
                ok = true;
                break;
            }
        }
        if (not ok) {
            NO();
            return;
        }
    }
    YES();
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
