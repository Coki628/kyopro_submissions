/*
・正攻法。こっちもやっとく。
・複数MODで確認する。案外すんなり行かなくて、
　まず1000桁文字列をMOD取ってModIntに変換する仕様も用意がなかった。
　で、確認方法を「3つやって2つ以上一致してたら」みたいにしてたんだけど、
　これだと狙われたケースに結構簡単にやられてしまうらしく、WAが取れなかった。
　「3つを合わせたものをキーとして確認」だと大丈夫みたいで、
　有名MOD3つでもちゃんと通った。
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
    ll N;
    cin >> N;
    vector<string> A(N);
    cin >> A;

    using mint2 = ModInt<1000000007>;
    using mint3 = ModInt<1000000009>;
    vector<mint> A1(N);
    vector<mint2> A2(N);
    vector<mint3> A3(N);
    map<array<int, 3>, int> C;
    rep(i, N) {
        A1[i] = A[i];
        A2[i] = A[i];
        A3[i] = A[i];
        C[{(int)A1[i], (int)A2[i], (int)A3[i]}]++;
    }
    ll ans = 0;
    rep(i, N) {
        rep(j, N) {
            auto res1 = A1[i] * A1[j];
            auto res2 = A2[i] * A2[j];
            auto res3 = A3[i] * A3[j];
            if (C.count({(int)res1, (int)res2, (int)res3})) {
                ans += C[{(int)res1, (int)res2, (int)res3}];
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
