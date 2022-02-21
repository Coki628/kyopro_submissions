/*
参考：https://codeforces.com/blog/entry/100153
・自力ならず。。
・ビットに帰着、MSB、種類数のDP、(2進数の)桁DP
・制約の2^PのPが10万くらいあったので、普通に考えると無理で、どうするか見えず。。
　こういう時は桁DPくらいしかないってのは頭に入ってたはずなのになー。
　2冪で言及してるんだから、2進数の桁毎に見るのは気付くべきだった。。
・で、それが分かったとして、種類数の数え上げなので重複を避ける工夫が要る。
　まずDP遷移を検討すると、通り数をMSB毎に管理するとして、
　「そのまま1ビットずらして末尾は1」か「そのまま2ビットずらして末尾は0」
　のどちらか。これが配るDPの頭だと分かりにくいんだけど、
　貰うDPで考えると、1ビット前と2ビット前から貰ってきた時に、
　ちょうど末尾が0になるやつと1になるやつなので、重複がなくて全部足していい、となる。
　この辺の理解も解説とか見てよくよく考えてやっと分かった感じ。
・これでDPの遷移では重複が発生しない確認が取れたので、次に初期値を検討する。
　あるA[i]を見た時、その状態に到達できる手段は末尾2ビットの状態から一意にできる。
　さっきのDP遷移をDP復元の時みたいに逆にやる感じ。(ソース内コメントも参照)
　これで0に向かってビットを削っていって、そこまでのA[i]のいずれかと重なれば重複、
　そうでないなら重複しないので必要な値、とする。
　これを値の小さい方から決めていけばいい。
　実際の数え上げのパートではここで必要と判定できた値だけを使用していく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N, P;
    cin >> N >> P;
    auto A = LIST(N);

    sort(ALL(A));
    set<ll> se;
    rep(i, N) {
        ll x = A[i];
        bool need = true;
        while (x) {
            // 末尾2ビットの状態を見る
            ll tail = x&3;
            // 01 or 11
            if (tail == 1 or tail == 3) {
                // 2x+1が使える
                x >>= 1;
            }
            // 00
            elif (tail == 0) {
                // 4xが使える
                x >>= 2;
            }
            // 10
            elif (tail == 2) {
                // 到達不可
                break;
            }
            if (se.count(x)) {
                need = false;
                break;
            }
        }
        if (need) {
            se.insert(A[i]);
        }
    }

    A = vector<ll>(ALL(se));
    N = A.size();
    ll L = 33;
    vector<ll> msb(L);
    rep(i, N) {
        rep(j, L-1, -1, -1) {
            if (A[i]>>j & 1) {
                msb[j]++;
                break;
            }
        }
    }

    // dp[i] := msbがiになる値の通り数(重複可能性を除いてあるので、種類数も同値とみなしていい)
    vector<mint> dp(P);
    rep(i, P) {
        if (i-1 >= 0) {
            dp[i] += dp[i-1];
        }
        if (i-2 >= 0) {
            dp[i] += dp[i-2];
        }
        if (i < L) {
            dp[i] += msb[i];
        }
    }
    mint ans = sum(dp);
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
