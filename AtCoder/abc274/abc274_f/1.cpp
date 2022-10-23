/*
参考：https://atcoder.jp/contests/abc274/editorial
・自力ならず。
・実数、何かを決めて全探索、式変形、イベントソート
・やはり黄diffになるような問題はむずい。
・ある魚iを基準として左端に置くとすると、
　他の魚の [iと同じ位置に来る時間,iの位置+lenに来る時間] が区間となる。
　魚の速度によって左右端は逆転するので適宜スワップ、
　速度が同じ場合はこの方法が使えないので、初期位置だけで判定する。
　左右端に該当する時間tl,trは 魚iの現在位置 = 魚jの現在位置
　みたいな式を立てて、これをtについて式変形すれば求まる。
　後はこの区間から重みWの総和が最大になる瞬間が見つかればいい。
　座圧して重み付きいもすみたいにしたくなるけど、
　実数で座圧がつらめな感じなので、イベントソートするのが良いようだ。
　右端は含める条件なので、同じ位置では追加が削除より先に来るようにする。
・これも結構重くて0.9秒くらいかかったんだけど、
　やっぱりldをdoubleにすると速くなって、0.64秒。
　誤差が怖い感じの実数の大小比較だけど、doubleでも問題なくACした。
　今度一応Fractionクラスでもやってみるかな。
　中身gcd取りまくりだから、むしろ浮動小数点より重そうだけど…。
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
    ll N, len;
    cin >> N >> len;
    vector<double> W(N), X(N);
    vector<ll> V(N);
    rep(i, N) {
        cin >> W[i] >> X[i] >> V[i];
    }

    ll ans = 0;
    rep(i, N) {
        vector<tuple<double, ll, ll>> events;
        ll sm = 0;
        rep(j, N) {
            // 速度が同じなら初期位置で判定
            if (V[j] == V[i]) {
                if (X[i] <= X[j] and X[j] <= X[i]+len) {
                    sm += W[j];
                }
            } else {
                // xi + t*vi = xj + t*vj を式変形
                double tl = (X[i]-X[j]) / (V[j]-V[i]);
                double tr = (X[i]-X[j]+len) / (V[j]-V[i]);
                if (tl > tr) swap(tl, tr);
                if (tr < 0) continue;
                chmax(tl, (double)0);
                events.eb(tl, 0, j);
                events.eb(tr, 1, j);
            }
        }
        sort(ALL(events));
        chmax(ans, sm);
        for (auto [pos, type, j] : events) {
            if (type == 0) {
                sm += W[j];
            } else {
                sm -= W[j];
            }
            chmax(ans, sm);
        }
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
