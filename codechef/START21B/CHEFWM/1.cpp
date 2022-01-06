/*
・自力AC！
・約数列挙、素数判定
・題意より、並べる列の高さはHの約数でかつ、互いに素である必要がある。
　素数なら大丈夫だよね、ということで約数列挙して素数判定した。
　(keijakさんの解法ツイートより、確かに素因数の種類数でよかったね。。)
　ここで得た個数を上限xとして、実際はWの約数でもないといけないので、
　Wの約数のうちx以下で最大の数を二分探索した。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

// 素数判定：O(√num)
bool is_prime(ll num) {
    if (num < 2) {
        return false;
    }
    if (num == 2 or num == 3 or num == 5) {
        return true;
    }
    if (num%2 == 0 or num%3 == 0 or num%5 == 0) {
        return false;
    }
    // 疑似素数(2でも3でも割り切れない数字)で次々に割っていく
    int p = 7;
    int step = 4;
    int num_sqrt = sqrt(num);
    while (p <= num_sqrt) {
        if (num%p == 0) {
            return false;
        }
        p += step;
        step = 6-step;
    }
    return true;
}

void solve() {
    ll W, H;
    cin >> W >> H;

    if (H == 1) {
        print(0);
        return;
    }
    auto divs1 = divisors(H);
    ll ans = 0;
    for (auto div : divs1) {
        if (is_prime(div)) {
            ans++;
        }
    }
    chmin(ans, W);
    auto divs2 = divisors(W);
    sort(ALL(divs2));
    ans = *--upper_bound(ALL(divs2), ans);
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
