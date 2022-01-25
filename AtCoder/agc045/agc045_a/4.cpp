/*
参考：https://qiita.com/Sooh31/items/97e2d9724fe47ed238b3
　　　https://sen-comp.hatenablog.com/entry/2020/11/20/043932
・XOR基底
・せっかく履修したので、過去にこれを使った問題を解いてみる。
　ゲームの考察パートはむずいので、あくまでXOR周りの判定のverifyとして。
・このXOR基底の考え方を使えば、ある数列Aの要素をXORして作れる全通りの要素を
　作るために必要最低限の要素たちを持っておける。(これがXOR基底)
　で、ある値aが今の手持ちの基底で作れるかどうかは、
　そのaで基底の処理をやった時に、新たな基底となるかどうかで判定できる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

template<typename T>
vector<T> get_xor_basis(const vector<T> &A) {
    vector<T> basis;
    for (auto a : A) {
        for (auto b : basis) {
            chmin(a, a^b);
        }
        if (a > 0) basis.eb(a);
    }
    return basis;
}

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    string S;
    cin >> S;

    vector<ll> basis;
    rep(i, N-1, -1, -1) {
        // 先手番なら今回のA[i]を基底に取り込む
        if (S[i] == '0') {
            for (auto b : basis) {
                chmin(A[i], A[i]^b);
            }
            if (A[i] > 0) basis.eb(A[i]);
        } else {
            // これまでの値の集合による基底でA[i]を作れるかどうか
            for (auto b : basis) {
                chmin(A[i], A[i]^b);
            }
            if (A[i] > 0) {
                print(1);
                return;
            }
        }
    }
    print(0);
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
