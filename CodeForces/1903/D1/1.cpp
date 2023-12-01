/*
・自力ならず。Cよりこっちのが目あったかもな。
・ビット演算、全体AND、クエリ、構築
・上位ビットから貪欲、オーバーフロー対策
・実は上位ビットから貪欲に、操作回数が足りるなら合わせる、を繰り返せばOK。
　本番中もそれ考えた気がしたんだけど、
　確か値が変化すると最適な行動は変わってしまう気がして、棄却しちゃったんだよな。
　よく考えるとビット毎なんだから、上位ビットを立たせる手段があるのなら、
　下位がどうなろうとそれを優先するべきなんだよね。
　下位ビット全部合わせたって上位1個に敵わないんだから。
　で、ここで1つ問題になるのが、ビットbが立ってなかった場合にそのA[i]のビットbをどう立たせるか。
　これはちょっと考えると、次にbが立つ最初の値が良くて、今立ってない訳だから、
　これはA[i]のbビット目未満を全0にしたもの+bビット目を立たせれば達成できる。
　公式解説は賢く計算一発で求めていたけど、
　bビット目未満をマスクで消す方法なら自分にも思いついた。
　これで欲しい値が分かれば、今のA[i]からの単純な引き算で操作回数は求まる。
　これでだいたいベースとなる部分はOK。貪欲に構築なので、
　コピー作っといて失敗したら状態戻す、みたいにやる。
　最後に引っかかるのがオーバーフロー。最悪で2^59*N回くらい加算が行きそうなので、
　途中でチェックして適宜breakさせる。これで無事AC。
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
    vector<ll> A(N);
    cin >> A;

    const ll M = 60;
    rep(_, Q) {
        ll k;
        cin >> k;
        ll ans = 0;
        auto bk = A;
        rep(b, M - 1, -1, -1) {
            ll needsm = 0;
            auto bkbk = A;
            bool ok = true;
            rep(i, N) {
                if (!(A[i] >> b & 1)) {
                    // bビット目以上だけ残すmsk
                    ll msk = ((1LL << M) - 1) - ((1LL << b) - 1);
                    // A[i]のbビット目未満を全0にしたもの
                    ll res = (A[i] & msk) | 1LL << b;
                    ll need = res - A[i];
                    // 最悪で2^59*Nくらい行きそうなのでオーバーフロー対策
                    if (add_overflow(needsm, need)) {
                        ok = false;
                        break;
                    }
                    needsm += need;
                    A[i] = res;
                }
            }
            if (ok and needsm <= k) {
                k -= needsm;
                ans += 1LL << b;
            } else {
                A = bkbk;
            }
        }
        print(ans);
        A = bk;
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
