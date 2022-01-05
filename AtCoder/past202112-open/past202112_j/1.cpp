/*
参考：https://imagingsolution.net/imaging/affine-transformation/
　　　https://imagingsolution.net/math/rotate-around-point/
　　　https://thira.plavox.info/blog/2008/06/_c.html
　　　http://sssiii.seesaa.net/upload/detail/image/affine_004.PNG.html
・自力ならず。大変だった。でも色々学べたのでOK。
・行列、アフィン変換
・解説見ると、実際は場合分けで解ける問題だったんだけどね…。
　一見して、abc189_eみたいなアフィン変換で解くのを考えてしまった。
　でもその方針でも理屈上は行けると思ったので、粘ってそっちで通した。
・概ねこのやり方でも良かったんだけど、サンプル通って他全部WAっていう地獄を見た。
　おかげでランダムテストの練習できたけどね。
・結局、回転すればx,y座標の位置関係が逆になるし、フリップすれば、
　回転方向の向きも逆になる、っていうのが考慮されてないのがダメだった。
　そこをちゃんとしたら無事AC。20万クエリで行列の乗算やってるけど速度も問題ない。
・回転とか反転の中心が普通にやると.5になるんだけど、まあ小数でやっても通った。
　その後、一応2倍すれば整数のままできるからここではその状態にしてある。
・ちょうどよかったので、アフィン行列周りの関数を整理しておいた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// 行列の積
template<typename T>
vector<vector<T>> mat_dot(const vector<vector<T>> &A, const vector<vector<T>> &B) {
    int n1 = A.size();
    int n2 = A[0].size();
    int m2 = B[0].size();
    auto res = list2d(n1, m2, (T)0);
    rep(i, n1) {
        rep(k, n2) {
            if (A[i][k] == 0) continue;
            rep(j, m2) {
                res[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return res;
}

// アフィン行列の逆行列
template<typename T>
vector<vector<T>> affine_mat_inverse(const vector<vector<T>> &a) {
    auto res = a;
    res[0][0] *= -1;
    res[1][1] *= -1;
    return res;
}

// (x, y)を中心に時計回り90度回転
template<typename T>
vector<vector<T>> rot90(T x, T y) {
    const vector<vector<T>> res = {
        {0, 1, x-y},
        {-1, 0, y+x},
        {0, 0, 1},
    };
    return res;
}

// (x, y)を中心に反時計回り90度回転
template<typename T>
vector<vector<T>> rot270(T x, T y) {
    const vector<vector<T>> res = {
        {0, -1, x+y},
        {1, 0, y-x},
        {0, 0, 1},
    };
    return res;
}

// x = p で反転
template<typename T>
vector<vector<T>> flip_x(T p) {
    const vector<vector<T>> res = {
        {-1, 0, 2*p},
        {0, 1, 0},
        {0, 0, 1},
    };
    return res;
}

// y = p で反転
template<typename T>
vector<vector<T>> flip_y(T p) {
    const vector<vector<T>> res = {
        {1, 0, 0},
        {0, -1, 2*p},
        {0, 0, 1},
    };
    return res;
}

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vector<string> grid(N, string(N, '0'));
    vvl base = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };
    // 座標を原点にずらすdx,dy
    ll dx = N-1, dy = N-1;
    // xyと回転方向の反転状態
    int xy_rev = 0, rot_rev = 0;
    rep(i, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, y;
            cin >> x >> y;
            x--; y--;
            // 今の(x,y)座標が元々あった位置を更新する
            vvl cur = {
                // 中心を原点に移動(2倍して整数のままやる)
                {x*2-dx},
                {y*2-dy},
                {1},
            };
            cur = mat_dot(affine_mat_inverse(base), cur);
            x = (cur[0][0]+dx)/2, y = (cur[1][0]+dy)/2;
            grid[x][y] = grid[x][y] == '0' ? '1' : '0';
        } elif (op == 2) {
            char c;
            cin >> c;
            if ((c == 'A') ^ rot_rev) {
                base = mat_dot(rot90(0LL, 0LL), base);
            } else {
                base = mat_dot(rot270(0LL, 0LL), base);
            }
            xy_rev ^= 1;
        } else {
            char c;
            cin >> c;
            if ((c == 'A') ^ xy_rev) {
                base = mat_dot(flip_x(0LL), base);
            } else {
                base = mat_dot(flip_y(0LL), base);
            }
            rot_rev ^= 1;
        }
    }
    // 各座標について現在の位置を特定して01を決める
    vector<string> ans(N, string(N, '*'));
    rep(x, N) {
        rep(y, N) {
            vvl cur = {
                {x*2-dx},
                {y*2-dy},
                {1},
            };
            cur = mat_dot(affine_mat_inverse(base), cur);
            ll cx = (cur[0][0]+dx)/2, cy = (cur[1][0]+dy)/2;
            ans[x][y] = grid[cx][cy];
        }
    }
    rep(i, N) {
        print(ans[i]);
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
