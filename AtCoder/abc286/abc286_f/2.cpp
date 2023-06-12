/*
参考：https://atcoder.jp/contests/abc286/editorial/5588
・upsolved。自力ならず。
・インタラクティブ、CRT
・結局の所、CRTへの理解度が足りなくて詰め切れなかった。
　CRTが復元できる値の上限は、lcm(crtに詰める全mod)になるようだ。
　で、本問の上限となる110個以下の要素で下から全部素数でやるとこれがちょっと足りないので求まらない。
　これの2,3をひとつ掛けて4,9にすると、要素110個にはまだちょうどよく収まるし、
　lcmが10億以上になって、うまく答えを求めることができる。
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

#include "numbers/Eratosthenes.hpp"
#include "acl/math.hpp"

Eratosthenes era(100007);
const ll MX = 110;

#ifdef __LOCAL
ll N = 2;

vector<ll> calc(vector<ll> A) {
    ll n = A.size();
    vector<ll> cur(n);
    iota(ALL(cur), 0);
    rep(_, N) {
        vector<ll> nxt(n);
        rep(i, n) {
            nxt[i] = A[cur[i]];
        }
        cur = nxt;
    }
    return cur;
}
#endif

void solve() {
    vector<ll> A;
    vector<pll> P;
    ll p = 2, offset = 0, mul = 1;
    while (1) {
        while (not era.is_prime(p)) p++;
        ll n = p;
        if (n == 2) {
            n *= 2;
        } else if (n == 3) {
            n *= 3;
        }
        if (A.size() + n > MX or mul_overflow(mul, n)) break;
        rep(i, n - 1) {
            A.eb(offset + i + 1);
        }
        A.eb(offset);
        P.eb(offset, n);
        mul *= n;
        offset += n;
        p++;
    }
    assert(mul >= 1000000000);

    ll M = A.size();
    vector<ll> B(M);
#ifdef __LOCAL
    B = calc(A);
#else
    A++;
    cout << M << endl;
    cout << A << endl;
    cin >> B;
    B--;
#endif
    vector<ll> R, mod;
    for (auto [i, p] : P) {
        R.eb(B[i] - i);
        mod.eb(p);
    }
    auto [y, z] = atcoder::crt(R, mod);
    assert(y <= 1000000000);
    cout << y << endl;
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
