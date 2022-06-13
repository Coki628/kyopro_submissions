/*
・きっちり自力AC！
・インタラクティブ、二分探索
・前から1字ずつ見て行く。出現済の文字種数cntを持っておく。
　前回出現した場所と文字種のペアも配列に持っておく。
　[0,i+1)でクエリ2を投げてcntが増えたらクエリ1で文字種を確認。
　増えなかったら既に出現済のどれかなので、ペア配列を使って、
　出現位置+1を左端としてクエリ2を試していって、文字種が減らない場所が今回の文字。
　これを愚直にやるとN*26かかってクエリ数が無理だけど、
　にぶたんするとN*5くらいになるので6000に収まる。
　前回出現位置を更新する時は愚直に配列いじっていい。(どうせ長さ26以下なので)
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

ll ask1(ll i) {
    char res;
    cout << "? " << 1 << ' ' << i+1 << endl;
    cin >> res;
    return res;
}

ll ask2(ll l, ll r) {
    ll res;
    cout << "? " << 2 << ' ' << l+1 << ' ' << r << endl;
    cin >> res;
    return res;
}

void answer(string S) {
    cout << "! " << S << endl;
}

void solve() {
    ll N;
    cin >> N;

    string ans;
    ll cnt = 0;
    vector<pair<ll, char>> cur;
    rep(i, N) {
        ll res = ask2(0, i+1);
        if (res > cnt) {
            assert(res == cnt+1);
            char c = ask1(i);
            cur.eb(i, c);
            ans += c;
            cnt++;
        } else {
            assert(res == cnt);
            ll j = bisearch_min(-1, cur.size(), [&](ll x) {
                ll res2 = ask2(cur[x].first+1, i+1);
                return res2 == cur.size()-x;
            });
            char c = cur[j].second;
            cur.erase(find(ALL(cur), cur[j]));
            cur.eb(i, c);
            ans += c;
        }
    }
    answer(ans);
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
