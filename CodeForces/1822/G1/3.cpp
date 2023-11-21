/*
参考：https://twitter.com/kude_coder/status/1650548633853648897
・自力ならず。
・3つ組、約数列挙、式変形
・終了後、TLの話を見ながら再挑戦。
　平方数からではなく、Aiの約数に注目した。
　さらに同じ高度合成数使われまくったりして時間かかってるかもと思い、
　同じAiをまとめて計算するようにした。がしかし通用せず。
　と思ったら、isqrtのにぶたんが重かったようで、純正sqrtに変えたら0.92秒で間に合った。
　あとAiを固定してるつもりだったけど、固定してるのAkだった。。(ソース内コメント修正済)
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll ans = 0;
    auto C = Counter(A);
    for (auto [k, v] : C) {
        ans += v * (v - 1) * (v - 2);
    }
    // Akを固定
    // Ai*b^2 = Aj*b = Ak となる3つ組を探す
    for (auto [a, cnt] : C) {
        for (auto bb : FastPrimeFactorization::divisors(a)) {
            if (bb == 1) continue;
            // 平方数だったらb^2部分として使える
            ll b = sqrt(bb);
            if (b * b == bb) {
                // Ai * Aj * Ak
                if (C.count(a / b) and C.count(a / bb)) {
                    ans += C[a / bb] * C[a / b] * cnt;
                }
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
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
