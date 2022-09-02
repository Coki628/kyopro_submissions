/*
・dojo set_e_7_2
・なんとか自力AC…。
・重複組み合わせ、素因数分解
・めちゃくちゃ色々ガチャガチャやった末、規則性をエスパーして押し通した。。
・各Mについて1～Nを並べると、強烈な二項係数臭が漂う。
　その線で探ると、素数冪だとnHr(N, 素因数の個数)で答えが合う。
　素数*素数だとN*N、ということはこれはnHr(N, 1)*nHr(N, 1)っぽい。
　なら任意の素因数にnHrして全部掛け合わせたら合うんじゃないか、合った。AC！みたいな。
・なんとかなったのはいいけど、こういう考察しかできないから成長しないんよなー…。
　これが水diffなのとかを見ると、全人類の数え上げ考察力の高さに涙を流すしかない。。
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

#include "numbers/Eratosthenes.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    Eratosthenes era(M, false);
    ModTools<mint> mt(N+1000);
    mint ans = 0;
    rep(j, 1, M+1) {
        mint cur = 1;
        for (auto [k, v] : era.factorize(j)) {
            cur *= mt.nHr(N, v);
        }
        ans += cur;
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
