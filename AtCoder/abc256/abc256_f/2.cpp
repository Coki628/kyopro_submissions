/*
参考：https://twitter.com/kyopro_friends/status/1538157667050749952
　　　https://twitter.com/rosso016/status/1538691942585815041
・行列セグ木
・この問題の累積和の遷移を整理すると、
　B[i] = B[i-1] + A[i]
　C[i] = C[i-1] + B[i]
　D[i] = D[i-1] + C[i]
　から、
　C[i] = C[i-1] + B[i-1] + A[i]
　D[i] = D[i-1] + C[i-1] + B[i-1] + A[i]
　とできて、この遷移をDPだと思うと行列に乗る。
　すると、行列累乗の時みたいに、行列の積で遷移をまとめられる。
　同じ遷移ではないので累乗ではないけど、セグ木に乗せれば高速に、
　1点(1行列)更新・区間(行列)積取得ができる。遷移を1個の行列にまとめたら、
　あとは行列累乗の時と同じ感じで初期値の行列と掛ければ答えが出る。
・ちょっとハマったのが、行列の積なのでマージ方向を気にすること。
　これは前にアフィン変換の行列積やった時にも思ったんだけど、
　行列セグ木は前にcf_edu_seg1_4bでそれを考慮しなくても通していたので、
　今回も大丈夫だと思ってたら、答え合わないのはそれが原因だった。
　わどさんが行列セグ木解を出していたのでそれを確認して気付けた。
・セグ木の演算に4^3が乗るので結構遅いかもと思ったけど、
　等差数列の遅延セグ木より速くて0.43秒。
　多分arrayでやってるのが良くて、vectorだとだいぶ遅くなると思う。
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

// 区間行列積取得
struct Node {
    // 2次元arrayの初期化は{}をひとつ多く括る
    array<array<mint, 4>, 4> mat{{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    }};
    Node(const array<array<mint, 4>, 4> &mat) : mat(mat) {};
    Node() {}
};
auto f = [](const Node &a, const Node &b) -> Node {
    // マージ方向をb,aにする
    return mat_dot(b.mat, a.mat);
};
const Node T = Node();

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    auto seg = get_segment_tree(N, f, T);
    rep(i, N) {
        array<array<mint, 4>, 4> mat{{
            {1, 0, 0, A[i]},
            {1, 1, 0, A[i]},
            {1, 1, 1, A[i]},
            {0, 0, 0, 1},
        }};
        seg.set(i, mat);
    }
    seg.build();
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, v;
            cin >> x >> v;
            x--;
            A[x] = v;
            array<array<mint, 4>, 4> mat{{
                {1, 0, 0, A[x]},
                {1, 1, 0, A[x]},
                {1, 1, 1, A[x]},
                {0, 0, 0, 1},
            }};
            seg.update(x, mat);
        } else {
            ll x;
            cin >> x;
            x--;
            auto res = seg.query(0, x+1);
            array<array<mint, 1>, 4> init{{
                {0},
                {0},
                {0},
                {1},
            }};
            print(mat_dot(res.mat, init)[2][0]);
        }
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
