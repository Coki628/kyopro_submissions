/*
・自力ならず。。
・全区間(l,r)について求める、区間xor、区間長
・ビット毎に見る、累積xor、左端を覚えて右端で貰うテク
・強い人はみんなこれかなり早く解いていて、
　ここまで典型に落とし込めているのが分かる。悔しいなー。
・結局区間長による重み付けをどう落とし込むかで詰め切れなかった。
・ビット毎にはしておくとして、どういう区間が寄与するか考えると、
　(累積xorの列にしておけば)右端と左端で偶奇の異なるものが該当する。
　区間の数を数えるならこれであと右端固定で該当する左端の数数えるくらいでいいんだけど、
　区間長で重み付けしないといけないので更に工夫が要る。やり方は、
　右端として見た後、左端で使う時のために区間長の和を計上する。
　これで該当する区間の左端を(区間長込みで)まとめて取得できる。
　右端はというと、固定するので個々の長さはいいとして、個数が要る。
　これは上記の和を取っていく時に個数も取っておけばいい。
　両方合わせると、左端も右端も該当する全区間のものをまとめて取得できるので、
　これを区間1個の時と同様に「右端-左端」すれば全区間分の区間和が取れる。
　これが分かれば、偶奇逆も同様にやるだけ。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    mint ans = 0;
    rep(b, 30) {
        // 累積xorを作って区間xorを取れるようにしておく
        vector<ll> B(N + 1);
        rep(i, N) {
            B[i + 1] = B[i] ^ (A[i] >> b & 1);
        }
        ll lensm0 = 0, lensm1 = 0, cnt0 = 0, cnt1 = 0;
        mint res = 0;
        // 位置rを右端とする区間をまとめて計算
        rep(r, N + 1) {
            if (B[r] == 0) {
                // cnt1: 位置rと偶奇が異なる左端の個数
                // lensm1: 位置rと偶奇が異なる左端の区間長の和
                res += r * cnt1 - lensm1;
                // 左端として使う時のためにこの右端を個数と和に計上する
                lensm0 += r;
                cnt0++;
            } else {
                res += r * cnt0 - lensm0;
                lensm1 += r;
                cnt1++;
            }
        }
        ans += res * (1LL << b);
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
