/*
参考：https://codeforces.com/blog/entry/108153
・この前のupsolveした。
・行列セグ木、平面走査、主客転倒
・セグ木に行列を乗せる話はネタバレしてたけど、その先はちゃんと自分で考察した。
　全通りの和なのでいつも通り主客転倒して寄与を考える。
　すると値1つ1つに注目すれば、それが最終的にどうなるかはビット演算ぽく表せそうだ。
　各集合で存在する値は区間になっているので、これは平面走査っぽく縦に持てる。
　演算3通りはDP遷移3通りを表す遷移行列を、その位置にある値が0か1で2つ作る。
　これで値の0,1が変化した時にセグ木に入れた行列も更新すれば、
　値毎に演算後に1となっている通り数を適切に取得できる。
　ただし少し素直に行かないのが、演算はN-1回なので、演算を表す行列をN個ではなく
　N-1個で表す。S1の分は初期値にしておく。とやる必要がある。
　この時セグ木の中でのマージ順は結合法則があるから自由なんだけど、
　初期値にはちゃんとS1を使わないといけない。
　添字ずらすのがめんどくて、最初初期値をSn-1にしててずっとバグってた…。
　考えてみればそれはそうな気もするけど、中々気付けなかった。。
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

#include "matrix/mat_dot.hpp"

struct Node {
    // 2次元arrayの初期化は{}をひとつ多く括る
    array<array<mint, 2>, 2> mat{{
        {1, 0},
        {0, 1},
    }};
    Node(const array<array<mint, 2>, 2> &mat) : mat(mat) {};
    Node() {}
    bool operator==(const Node &f) const {
        return mat == f.mat;
    }
    operator array<array<mint, 2>, 2>() const { return mat; }
};
auto f = [](const Node &a, const Node &b) -> Node {
    // マージ方向をb,aにする
    return mat_dot(b.mat, a.mat);
};
const Node T = Node();

void solve() {
    array<array<mint, 2>, 2> zero = {{
        {3, 1},
        {0, 2},
        // A[i-1] == 0 の遷移
        // dp[i][0] = dp[i-1][0]*3 + dp[i-1][1]*1;
        // dp[i][1] = dp[i-1][0]*0 + dp[i-1][1]*2;
    }};
    array<array<mint, 2>, 2> one = {{
        {1, 1},
        {2, 2},
        // A[i-1] == 1 の遷移
        // dp[i][0] = dp[i-1][0]*1 + dp[i-1][1]*1;
        // dp[i][1] = dp[i-1][0]*2 + dp[i-1][1]*2;
    }};
    array<array<mint, 1>, 2> init = {{
        {1},
        {0},
    }};
    ll N;
    cin >> N;
    vvl in(300007), out(300007);
    rep(i, -1, N-1) {
        ll l, r;
        cin >> l >> r;
        in[l].eb(i);
        out[r].eb(i);
    }

    auto seg = get_segment_tree(N-1, f, T);
    rep(i, N-1) {
        seg.set(i, Node(zero));
    }
    seg.build();
    mint ans = 0;
    rep(i, 300007) {
        for (auto j : in[i]) {
            if (j == -1) {
                init = {{
                    {0},
                    {1},
                }};
            } else {
                seg.update(j, one);
            }
        }
        auto res = mat_dot(seg.all().mat, init);
        ans += res[1][0];
        for (auto j : out[i]) {
            if (j == -1) {
                init = {{
                    {1},
                    {0},
                }};
            } else {
                seg.update(j, zero);
            }
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
