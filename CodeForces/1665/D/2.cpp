/*
参考：https://twitter.com/kude_coder/status/1512475392929853440
　　　https://twitter.com/butsurizuki/status/1512469875608133636
・自力ならず。そこそこ近い方針はやったんだけど。
・インタラクティブ、GCD、中国剰余定理
・自力の方針でgcd(a,b)==b-aなら、mod(b-a)でx=b-a-a、みたいなことを思ってやったけど、
　これはもっと一般化できて、gcd(a,b)==gとして、mod gでx=g-aが常に成り立つ模様。
　で、素因数たくさん使った方が嬉しそうだなってのもまあ合ってて、
　ただしこの素因数を個別に差分として使うんじゃなくて、
　全部掛けて1つの大きい数にして、それを固定された差分として使う、だった。
　ただし素因数だけ適当に掛けると、制約の条件をうまく満たさないので
　適当に2とかも追加で掛けて微調整する。
　この大きい数を差分に使って左端の方を動かせば、
　mod gでx=g-aの条件がたくさん集まるので、これをCRTに突っ込めば答えが出る。
・ところで今回#ifdef __LOCALをうまく使って、ローカル作業時には
　自作のクエリ返答用関数使ってシミュをやったら、デバッグがかなり楽になった。
　これは今後も使えそうだ。
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

#include "numbers/Eratosthenes.hpp"

#include "acl/math.hpp"
using namespace atcoder;

Eratosthenes era(200);
vector<ll> primes;
ll diff = 1;
void prep() {
    rep(i, 200) {
        if (era.is_prime(i)) {
            primes.eb(i);
        }
    }
    // 素因数が多くて10億以上20億以下(クエリの制約)の値を用意する
    ll i = 0;
    while (diff*primes[i] <= (ll)1e9*2) {
        diff *= primes[i];
        i++;
    }
    while (diff*2 <= (ll)1e9*2) {
        diff *= 2;
    }
}

ll x = -1;
ll calc(ll a, ll b) {
    return gcd(x+a, x+b);
}

// インタラクティブ用
ll ask(ll a, ll b) {
    ll res;
    cout << "? " << a << ' ' << b << endl;
    #ifdef __LOCAL
        res = calc(a, b);
        cout << res << endl;
    #else
        cin >> res;
    #endif
    return res;
}

void answer(ll i) {
    cout << "! " << i << endl;
}

void solve() {
    #ifdef __LOCAL
        cin >> x;
    #endif
    vector<ll> A, B;
    rep(a, 1, 30) {
        ll res = ask(a, a+diff);
        if (res >= 2) {
            A.eb(modulo(res-a, res));
            B.eb(res);
        }
    }
    #ifdef __LOCAL
        debug(A.size());
    #endif
    auto [y, z] = crt(A, B);
    answer(y);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    prep();

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
