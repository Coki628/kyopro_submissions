/*
参考：https://twitter.com/KaikeyPro/status/1754916225938084131
・自力ならず…。悔しい。
・順列、連続部分列、総和、mod K、偶奇
・長さKの連続部分列をずらしてくんだけど、この時、和の差分が1以下であるには、
　その時左から出た要素と右から入った要素の差分が1である必要がある。
　なのでmod K毎に差分1の要素を入れていく。ここまではやった。
　これだと1つずらした時点は個別には大丈夫なんだけど、
　離れた場所にある部分列まで全部差分1以内で収まるとは限らない。
　本番中は時間なくて最後あんま考えられなかったのもあり、ここから先詰められなかった。
　で、どうすればよかったか。例えば最初の区間和をXとして、
　次に入ってくる要素のが出る要素より1大きいなら2番目はX+1になる。
　もう1つずらした時にX+2になるようではダメで、X-1にする必要がある。
　そうなると、出る要素と入る要素の大小は、区間をずらした時に交互でないといけない。
　よって最初の左端の偶奇で増減どっちに向けるか決める。
　mod Kが同じ所は差分1でないといけないので、差分K毎にまとめて決めてく。
　これだけ考えると真ん中らへんが綺麗にまとまるか
　ぱっとイメージできないけど、手元でちょっと試すと問題なさそう。
　実際、これで投げると通る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, K;
    cin >> N >> K;

    vector<ll> ans(N);
    ll p1 = 1, p2 = N;
    rep(i, N) {
        if (ans[i] != 0) continue;
        rep(j, i, N, K) {
            ans[j] = i % 2 == 0 ? p1++ : p2--;
        }
    }
    print(ans);
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
