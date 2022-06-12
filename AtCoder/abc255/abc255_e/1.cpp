/*
参考：https://twitter.com/rosso016/status/1535637212452139008
・自力ならず…。いやー普通にむずかった。
・式変形
・まず一番の敗因はM<=10に気付いたのが終了10分前くらいだったこと。
　それに気付いても結局具体的な方針は見えなかったんだけどね…。
・問題設定を確認すると、A[0]を決めれば他の場所は芋づる式に決まると分かる。
　ここでA[0]を0とか適当な値に決めて、数列の後ろの方を仮で決めた状態にしてから、
　うまいこと式変形とかできないか考える。結果的に方針はこれで合ってたんだけど、
　そのうまいこと式変形がどうするか見えなかったので結局無理だった感じ…。
・正解は「A[0]を何にすればA[i]がXのどれか0~Mと合うか？」をi,jで全探索する、だった。
　ある位置A[i]をX[j]と合わせようと思った時、さっきのA[0]=0で決めた列をBとすると、
　偶奇によってA[i]=B[i]+A[0]かA[i]=B[i]-A[0]のどちらかで、
　このA[i]をX[j]と置けば、X[j]=B[i]+A[0] => X[j]-B[i]=A[0] のように式変形できるので、
　A[0]として欲しい値が一意に定まる。これをi,j全部見て、一番多く出現した値が答え。
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
    ll N, M;
    cin >> N >> M;
    auto S = LIST(N-1);
    auto X = LIST(M);

    // 仮でA[0]=0とした時の結果の列を作る
    vector<ll> B;
    B.eb(0);
    rep(i, N-1) {
        B.eb(S[i]-B.back());
    }

    map<ll, ll> C;
    rep(i, N) {
        rep(j, M) {
            // A[0]に何を置けばA[i]==X[j]となるかを式変形して求める
            ll a0 = X[j] - B[i];
            if (i%2 == 1) {
                a0 = -a0;
            }
            C[a0]++;
        }
    }
    ll ans = most_common(C)[0].first;
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
