/*
・自力AC！
・インタラクティブ、乱択
・立っているビット数が返るので、その数に合わせて適当に選ぶとすると、
　うまくいく確率は1/8C1～8C8のどれかになって、
　300回試せることからそう悪くない勝算にならないかな、となる。
・最初の反転で終わるのを考慮してなくて、whileのp > 0の条件を入れたら通った。
　これもっと早く気付いてればR1通過だったと思うと悔やまれる…。
・しかもこれ、ビットが多くなったら反転させたんだけど、8C5も8C3も同じなんだから意味ないね…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "common/randrange.hpp"
#include "numbers/ntod.hpp"

string val = "00000000";

string sheft(string S) {
    ll r = randrange(0, 8);
    return S.substr(r)+S.substr(0, r);
}

int calc(string S) {
    ll b1 = ntod(val, 2);
    ll b2 = ntod(S, 2);
    ll b3 = b1 ^ b2;
    val = zfill(bin(b3), 8);
    return popcount(b3);
}

vector<vector<vector<ll>>> P(9);
void prep() {
    rep(bit, 1LL<<8) {
        vector<ll> v;
        rep(i, 8) {
            if (bit>>i & 1) {
                v.eb(i);
            }
        }
        P[popcount(bit)].eb(v);
    }
}

void solve() {
    #ifdef __LOCAL
        val = zfill(bin(randrange(1, 1LL<<8)), 8);
        // val = "11111111";
        debug(val);
    #endif
    ll qcnt = 0;
    ll p;
    #ifdef __LOCAL
        p = calc("00000000");
    #else
        cout << "00000000" << endl;
        cin >> p;
    #endif
    qcnt++;
    if (p >= 5) {
        #ifdef __LOCAL
            p = calc("11111111");
        #else
            cout << "11111111" << endl;
            cin >> p;
        #endif
        qcnt++;
    }
    while (p > 0 and qcnt <= 300) {
        ll i = randrange(0, P[p].size());
        string s(8, '0');
        for (auto j : P[p][i]) {
            s[j] = '1';
        }
        #ifdef __LOCAL
            p = calc(s);
        #else
            cout << s << endl;
            cin >> p;
        #endif
        qcnt++;
        if (p == -1) exit(0);
        if (p == 0) break;
        if (p >= 5) {
            #ifdef __LOCAL
                p = calc("11111111");
            #else
                cout << "11111111" << endl;
                cin >> p;
            #endif
            qcnt++;
            if (p == -1) exit(0);
        }
    }
    #ifdef __LOCAL
        debug(qcnt);
    #endif
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
    rep(i, 1, T+1) {
        // cout << "Case #" + tostr(i) + ": ";
        solve();
    }
    return 0;
}
