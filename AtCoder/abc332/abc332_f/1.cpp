/*
・自力ならず。。悔しい。
・期待値、遅延セグ木、区間乗算・区間加算
・しばらくサンプルをガチャガチャすると、それぞれの更新を
　ai = ai*(len-1)/len + x*1/len みたいにやると合うのが分かった。
　確かに変化がない確率が(len-1)/lenなので、これは道理も通ってる。
　サンプルエスパーみたいであまり良い方法じゃなかったけど、
　とりあえずこれの高速化を検討する。
　で、これをやるには区間への乗算→加算みたいな操作が必要。
　遅延セグ木の作用素に乗せたかったが、乗算と加算の組は今まで使ったことがなく難航。
　結局これが詰め切れず本番終了となった。
・で、方法はどうだったかと言うと、乗算→加算の操作はつまり、
　x <- ax+b みたいなものなので1次関数の合成関数をセグ木に乗せた時と
　全く同じ方法が可能だった。(aclpc_kでそのものずばりを作用素に乗せているし、
　要素側でもよければタコヤキのやつで乗せている。)
　式に抽象化されていると、具体例への適用の仕方がどうもぼやけちゃうよな。
　ここで合成関数になるなんて全然見えなかった。
　(きっと数学強い人は見えるんだろうけども)
・乗算と加算がバラバラに適用されるようなケースでも任意に対応できるのかは
　未verifyだけど、それはいつかそういう問題に出会った時にこれを使ってみよう。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間乗算・区間加算・1点取得
struct Func {
    mint mul, add;
    bool operator==(const Func &f) const {
        return mul == f.mul and add == f.add;
    }
};
auto f = [](mint a, mint b) -> mint { return a; };
auto g = [](mint a, Func b) -> mint {
    return a * b.mul + b.add;
};
// ax + b の合成関数
// h2(h1(x))
// c * h1(x) + d
// c * (ax + b) + d
// c * ax + c * b + d
// {c * a, c * b + d}
auto h = [](Func a, Func b) -> Func {
    return {b.mul * a.mul, b.mul * a.add + b.add};
};
const mint T = 0;
const Func E = {1, 0};

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<mint> A(N);
    cin >> A;

    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, A[i]);
    }
    seg.build();
    rep(i, M) {
        ll l, r;
        mint x;
        cin >> l >> r >> x;
        l--;
        mint len = r - l;
        seg.update(l, r, {(len - 1) / len, x * ((mint)1 / len)});
        // rep(j, l, r) {
        //     A[j] = A[j] * ((len - 1) / len) + x * ((mint)1 / len);
        // }
    }
    print(seg);
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
