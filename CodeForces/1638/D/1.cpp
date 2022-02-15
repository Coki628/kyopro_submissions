/*
・これは終了後TLE。
・逆操作で見ると、先に確定した所はもう何置いてもいいみたいになる。
　4マスに何が書いてあるか(H-1)*(W-1)個持っておいて、
　自由マス含め4つ揃った所からやる。1つやった後、周囲8箇所を更新。
　{cnt[i], i}みたいなsetで更新しながら大きい方から処理してった。
・さすがに1000^2グリッド*8方向にsetのlogとか乗るのはきついようでTLE。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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



void solve() {
    ll H, W;
    cin >> H >> W;
    vvl grid(H);
    rep(i, H) {
        grid[i] = LIST(W);
    }

    // 右上が(h,w)な4マスの同じ色(+自由色)の数を数える
    auto count = [&](ll h, ll w) -> ll {
        map<ll, ll> C;
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                C[grid[nh][nw]]++;
            }
        }
        ll res = 0;
        for (auto [k, v] : C) {
            if (k == -1) continue;
            chmax(res, v);
        }
        res += C[-1];
        return res;
    };
    // 右上が(h,w)な4マスを塗る(自由マスとする)。新規で塗ったマスの数を返す。
    auto paint = [&](ll h, ll w) -> ll {
        ll res = 0;
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                if (grid[nh][nw] != -1) {
                    grid[nh][nw] = -1;
                    res++;
                }
            }
        }
        return res;
    };
    // ここに含まれる色を返す
    auto color = [&](ll h, ll w) -> ll {
        rep(nh, h, h+2) {
            rep(nw, w, w+2) {
                if (grid[nh][nw] != -1) {
                    return grid[nh][nw];
                }
            }
        }
        return -1;
    };

    // 4マス揃った位置から優先して持つためのset
    set<pll> se;
    ll N = (H-1)*(W-1);
    // setを適切に更新するための個数を管理する配列
    vector<ll> cnt(N);
    rep(h, H-1) {
        rep(w, W-1) {
            ll i = gridtoid(h, w, W-1);
            cnt[i] = count(h, w);
            se.insert({cnt[i], i});
        }
    }
    // 塗り終えたマスの数
    ll donecnt = 0;
    vector<array<ll, 3>> ans;
    while (se.size() and donecnt < H*W) {
        // 4マス揃ってる方から優先して使う
        auto [mxcnt, i] = *--se.end(); se.erase(--se.end());
        auto [h, w] = idtogrid(i, W-1);
        if (mxcnt < 4) {
            print(-1);
            return;
        }
        // 今回塗る色
        ll c = color(h, w);
        if (c == -1) continue;
        donecnt += paint(h, w);
        ans.pb({h+1, w+1, c});
        // 周囲8マスの更新
        rep(nh, max(h-1, 0LL), min(h+2, H-1)) {
            rep(nw, max(w-1, 0LL), min(w+2, W-1)) {
                if (h == nh and w == nw) continue;
                if (color(nh, nw) == -1) continue;
                ll j = gridtoid(nh, nw, W-1);
                // setも合わせて更新する
                if (se.count({cnt[j], j})) {
                    se.erase({cnt[j], j});
                    cnt[j] = count(nh, nw);
                    se.insert({cnt[j], j});
                }
            }
        }
    }

    if (donecnt < H*W) {
        print(-1);
        return;
    }
    reverse(ALL(ans));
    print(ans.size());
    for (auto& arr : ans) print(arr);
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
