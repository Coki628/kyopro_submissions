/*
参考：https://twitter.com/4yAobz/status/1621555848605745152
　　　https://twitter.com/kude_coder/status/1621558812988821505
・自力ならず。
・セグ木で貪欲シミュ、BIT2本で個数と総和
・最初の1個だけ左でしか取れないので、基本的には左右から自由に選んで、
　その1つについてはどうにかする。までは行けたんだけど、
　その左に決める1つをどうにかするのが難しかった。
　左に決める1つを全探索、までは思いついたんだけど、
　普通に毎回シミュしたら2乗オーダーになっちゃうし、で詰んでた。
・とりあえず全部貪欲に取りきって、その状態から差分更新みたいに考える。
　この時点で左から取ったのが1つでもあれば、それを最初にすればいいのでOK。
　以下、全て右から取った場合として話を進める。
　どうやって差分更新するのか考える。A[i]を左で取る時のコストを、
　今取ったものをなるべく減らさずに確保したいので、
　コストが高い方から1個ずつ削っていくとする。
　これを愚直にやるとO(N)かかってしまうので、
　と思うと累積和にぶたんでいけそうだとなる。
　なんだけど、A[i]が既に右で取ったものだった場合、
　それを一旦前述の累積和から外す必要がある。
　そこでBITにぶたんが出てくる。1個抜いた状態での個数も管理したいので、
　これはBIT2本で個数と総和管理するやつにできる。
　ここまで来れば、後は適切に状態戻しとかやりながら
　N個のA[i]を左から取るのを全部試せばいい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    vector<ll> cost1(N), cost2(N);
    rep(i, N) {
        cost1[i] = i + 1 + A[i];
        cost2[i] = N - i + A[i];
    }
    auto seg1 = get_segment_tree(cost1, [](ll a, ll b) { return min(a, b); }, INF);
    auto seg2 = get_segment_tree(cost2, [](ll a, ll b) { return min(a, b); }, INF);
    ll cnt = 0, cur = K;
    bool useleft = false;
    vector<int> used(N);
    vector<pll> vec;
    // とりあえず全部左右選べるものとして貪欲シミュ
    rep(i, N) {
        ll mn1 = seg1.all();
        ll mn2 = seg2.all();
        if (mn1 <= mn2) {
            if (mn1 > cur) break;
            ll j = seg1.find_first(0, [&](ll x) { return x <= mn1; });
            cnt++;
            cur -= mn1;
            seg1.update(j, INF);
            seg2.update(j, INF);
            useleft = true;
        } else {
            if (mn2 > cur) break;
            ll j = seg2.find_first(0, [&](ll x) { return x <= mn2; });
            cnt++;
            cur -= mn2;
            seg1.update(j, INF);
            seg2.update(j, INF);
            used[j] = true;
            vec.eb(cost2[j], j);
        }
    }
    // 左が1つでもあれば、それを最初にすればいい
    if (useleft) {
        print(cnt);
    } else {
        vec.eb(0, -1);
        ll M = vec.size();
        // 降順に
        reverse(ALL(vec));
        BIT<ll> bitsm(M), bitcnt(N);
        vector<ll> NtoM(N, -1);
        rep(i, 1, M) {
            auto [val, j] = vec[i];
            bitsm.add(i, val);
            bitcnt.add(i, 1);
            NtoM[j] = i;
        }
        ll ans = 0;
        // A[i]を左で取る全探索
        rep(i, N) {
            if (used[i]) {
                cur += cost2[i];
                cnt--;
                bitsm.update(NtoM[i], 0);
                bitcnt.update(NtoM[i], 0);
            }
            ll need = max(cost1[i] - cur, 0LL);
            // 右から取ったのを何個捨てればA[i]を左で取れるか
            ll j = bitsm.bisearch_fore(0, M - 1, need);
            if (j != -1) {
                chmax(ans, cnt - bitcnt.query(0, j + 1) + 1);
            }
            if (used[i]) {
                cur -= cost2[i];
                cnt++;
                bitsm.update(NtoM[i], cost2[i]);
                bitcnt.update(NtoM[i], 1);
            }
        }
        print(ans); 
    }
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
