/*
参考：https://twitter.com/shobonvip/status/1706716914595267028
　　　https://codeforces.com/contest/1878/submission/225371033
・自力ならず。結構惜しいとこまで行ってただけに悔しい。
・約数の個数、GCD、互いに素
・素因数分解、素数冪で管理
・操作が乗算で約数の個数d(n)が知りたいので、素因数分解して素数冪にしておけば求まる。
　乗算の操作は素数冪のmapを適宜更新していけばいい。
　回答ではNに互いに素な値を乗じていって、d(n)をNと一致させられるかが問われる。
　これは適当な素数なりを使うとすると、元々のd(n)の2,3,4...倍になら
　約数の個数を変化させられる。つまりNがd(n)の倍数なら達成可能。これで判定できる。
・ここまで分かったのに、実装方針ミスってて通せなかった。
　d(n)をそのまま素因数を追加して更新してしまっていて、
　これだと先にやるはずの素数冪の加算を、各素因数で乗算した後にやるような形になってしまう。
　その素因数について一旦除算でクリアして、追加したい冪を加算してから再度乗算すればOK。
　何人かの提出と睨めっこして、くまくまさんの提出でその実装部分に気付けた。
・ちなみに素因数分解は毎回愚直にやって間に合うかちょっと心配したけど全然大丈夫だった。
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
    ll N, Q;
    cin >> N >> Q;
    map<ll, ll> C;
    ll cnt = 1;
    for (auto [k, v] : factorize(N)) {
        cnt *= v + 1;
        C[k] += v;
    }
    ll init = cnt;
    auto initc = C;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            for (auto [k, v] : factorize(x)) {
                // この素因数の分を一旦取り除く
                cnt /= C[k] + 1;
                C[k] += v;
                // 更新後、再度計上する
                cnt *= C[k] + 1;
            }
            // Nがcntの倍数ならOK
            bool ok = true;
            for (auto [k, v] : factorize(cnt)) {
                if (not C.count(k) or C[k] < v) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                YES();
            } else {
                NO();
            }
        } else {
            cnt = init;
            C = initc;
        }
    }
    print();
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
