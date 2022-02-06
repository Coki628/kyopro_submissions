/*
参考：https://atcoder.jp/contests/abc238/editorial
・これは解きたかったな。悔しい。
　自力は依存関係でグラフにしてDAGをどうにかやるみたいな方針を目指したけどこれが大ハズレ。
　とはいえ、3乗DPって聞いた後でゆっくり考えても詰められなかったので、
　結局Gに時間割いた方が今回はどっちにしても良かったね…。
・順列、状態をうまく持ってDP
・制約から3乗DPは想像できる。でもいい状態の持ち方とか思いつかずやめてしまった。
　とりあえずその方針で考えると、まず片側でソートしておいた方が、
　考えることが少なくなって良さそう、となる。で、DPするなら、
　「何番目まで見て」は欲しいし、答えとしてK人選ぶので「何人選んだか」も欲しい。
　制約的にここに状態Nくらいの添字もう1つか、小さい添字とNの遷移ループ、とかが考えられる。
　なんだけど何も出なかった。。
・必要だったのは「選ばなかった人のQでの最小がk」だった。
　確かにPでソート済なので大事なのはQでの順位で、今回の問題設定なら
　選ばなかった中での最高順位を持っておけば、
　それより低い順位の人は使えないのが分かるので適切に遷移を作れる。
・ここが理解できれば後はすぐで、普通にDP書いて、
　人iを選ぶ/選ばないの遷移を条件を満たすように適切に行えればOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto P = LIST(N);
    auto Q = LIST(N);
    vector<pll> PQ;
    rep(i, N) {
        PQ.eb(P[i], Q[i]);
    }

    sort(ALL(PQ));
    tie(P, Q) = zip(PQ);
    // dp[i][j][k] := i人目まで見て、j人選んで、選ばなかった人のQでの最小がkの時の通り数
    auto dp = list3d<mint>(N+1, K+1, N+2, 0);
    dp[0][0][N+1] = 1;
    rep(i, N) {
        rep(j, K+1) {
            rep(k, N+2) {
                // 選ぶ場合、Q[i]がkより小さい必要がある
                if (j+1 <= K and Q[i] < k) {
                    dp[i+1][j+1][k] += dp[i][j][k];
                }
                // 選ばない場合、kを更新する
                dp[i+1][j][min(k, Q[i])] += dp[i][j][k];
            }
        }
    }
    mint ans = sum(dp[N][K]);
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
