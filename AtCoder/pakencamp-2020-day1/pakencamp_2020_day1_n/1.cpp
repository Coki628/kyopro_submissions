/*
・その他埋めAC数上げ
・自力AC！
・なんか通っちゃったけど、想定解と違うんだけど嘘貪欲じゃないか心配だな…。
・まず考えたのは、任意の位置を任意の回数かけて消せる設定だけど、
　操作は1回が良くて2回以上やるのは無駄。例えば、[l1,r1],[l2,r2]を消したいのであれば、
　[l1,r2]で消す方がコストがかからなくて、これは一般に言える(はず)。
・これで操作の候補がN^2まで絞り込めたので、ここから左端を固定して右端を高速に探してみる。
　前提として左端も右端も、それぞれ端から見て昇順じゃなくなってしまう位置以降は使えない。
　そこを消してもソート済にならない箇所が絶対残ってしまうから。
　で、この条件で右端を見た時、右端の候補となる場所は(昇順じゃなくなる一番左を除いて)
　単調増加なので、にぶたんが使える。左端は固定しているので、この昇順な範囲から、
　左端位置(の1つ手前)より大きい最小位置を見つければ、これより右に右端を取る必要はなくなる。
　これでだいたいOKだけど、右端に決めた位置も消えるので、
　この1つ手前のにぶたんで条件を満たさなかった位置も候補として使える。
　この右端候補2つを両方試す。これを有効な左端全部でやって最小取ればOK。
・コストは消す位置の左右端でかかるけど、条件を満たすかチェックするのは
　消す左右端より1つ外側なので、添字管理がまあまあややこしい。
　とはいえ、基本的には条件整えたらにぶたんだけで済むので、
　これで600点は通らなそ～って思いながら投げて通ってしまったので、
　ちゃんと正当な方法だったのかはまあまあ心配ではある。
　ちなみに想定解はセグ木でDP高速化するやつだった。
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
    auto A = LIST(N);

    if (sorted(A) == A) {
        print(0);
        return;
    }

    A.eb(INF);
    // 右端の左限(この位置以降は昇順なので右端として自由に選べるし、単調性もあるのでにぶたんできる)
    ll rl = N;
    rep(i, N-1, 0, -1) {
        if (A[i-1] > A[i]) {
            rl = i;
            break;
        }
    }
    ll ans = INF;
    rep(l, N) {
        ll r = bisearch_min(max(rl-1, l), N, [&](ll x) {
            return (l > 0 ? A[l-1] : 0) < A[x];
        });
        // 位置r以降は残していいので、消す右端としてはr-1と両方試す
        chmin(ans, min(A[l]+A[r], A[l]+A[r-1]));
        // これ以降は左端として使えない
        if (l > 0 and A[l-1] > A[l]) break;
    }
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
