/*
参考：https://atcoder.jp/contests/abc236/editorial
・自力ならず。。
・二分探索、平均値の最大化、中央値の最大化
・いやー、これは解けたらよかった。でも自分じゃ出なかったかな。
　特に平均値の方は、完全に典型テクを忘れてた。
・類題はABC034_dとかABC044_cとか。平均を求める時は平均の分引いて総和0を目指す形にすると、
　ある要素の損得が定まったり、要素が何個あるかを考えなくてよくなるから見通しがよくなるってやつ。
　今回は個数を考えなくてよくなるので、直前を取った取らないの状態だけ持ったDPができるようになる。
　本当は整数にした方がよさそうだけど、小数にぶたんでも問題なく通った。
・中央値の方もどこかで見たことはあるかもしれないけど、
　こっちはにぶたんで行けると思えば、後は割と素直な貪欲で判定できる。
　m以上の値なら貪欲に取るとして、中央値に足るような個数を集まられるかみたいな。
　中央値の定義は下からceil(N, 2)って言ってるけど、
　実際は上から数えて半分取らなきゃいけないのでfloor(N, 2)+1だったりして、
　ちょっとちゃんと整理しないと混乱する。(した。)
・中央値の貪欲は思いついたとしても割と自信が持てなそうなので、こっちもDPを検討してみた。
　平均値と同じように目標を0地点として、ある値m以上か未満かで+1,-1の2値で管理すれば、
　同様に個数を考えなくてよくなる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "common/bisearch_real.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    ll M = max(A);

    ld avg = bisearch_max(0, M+1, [&](ld m) -> bool {
        vector<ld> B(N);
        rep(i, N) {
            B[i] = A[i]-m;
        }
        auto dp = list2d(N+1, 2, (ld)-INF);
        dp[0][1] = 0;
        rep(i, N) {
            rep(j, 2) {
                if (dp[i][j] <= -INF) continue;
                chmax(dp[i+1][1], dp[i][j]+B[i]);
                if (j == 1) {
                    chmax(dp[i+1][0], dp[i][j]);
                }
            }
        }
        return max(dp[N])+EPS >= 0;
    }, 30);

    ll mid = bisearch_max(0, M+1, [&](ll m) -> bool {
        vector<ll> B(N);
        rep(i, N) {
            B[i] = A[i] >= m ? 1 : -1;
        }
        auto dp = list2d(N+1, 2, -INF);
        dp[0][1] = 0;
        rep(i, N) {
            rep(j, 2) {
                if (dp[i][j] <= -INF) continue;
                chmax(dp[i+1][1], dp[i][j]+B[i]);
                if (j == 1) {
                    chmax(dp[i+1][0], dp[i][j]);
                }
            }
        }
        return max(dp[N]) > 0;
    });

    print(avg);
    print(mid);
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
