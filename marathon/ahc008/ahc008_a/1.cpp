/*
・初期解。まずはみんなやってた、ひたすら周囲に壁作るだけのやつ。これが1100万点くらい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "common/input.hpp"
#include "common/print.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "common/listnd.hpp"

const int GRID_SIZE = 30;
const int TURN_COUNT = 300;

bool blocked[GRID_SIZE][GRID_SIZE];
bitset<20> pets[GRID_SIZE][GRID_SIZE];
bitset<10> people[GRID_SIZE][GRID_SIZE];
// block
const string udlr = "udlr";
map<char, int> udlrrev = {
    {'u', 0}, {'d', 1}, {'l', 2}, {'r', 3},
};
// move
const string UDLR = "UDLR";
map<char, int> UDLRrev = {
    {'U', 0}, {'D', 1}, {'L', 2}, {'R', 3},
};

struct Pet {
    ll h, w, type;
};
struct Human {
    ll h, w;
};

// 到達可能範囲内のマス数とペット数を集計
pll bfs(ll sh, ll sw) {
    auto visited = list2d(GRID_SIZE, GRID_SIZE, false);
    queue<pii> que;
    que.push({sh, sw});
    pll res = {0, 0};
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        res.first++;
        res.second += pets[h][w].count();
        for (auto [dh, dw] : dir4) {
            int nh = h+dh, nw = w+dw;
            if (nh < 0 or nw < 0 or nh >= GRID_SIZE or nw >= GRID_SIZE) continue;
            if (blocked[nh][nw]) continue;
            if (not visited[nh][nw]) {
                visited[nh][nw] = true;
                que.push({nh, nw});
            }
        }
    }
    return res;
}

// ブロック可能なマスか判定
bool can_block(ll h, ll w) {
    if (blocked[h][w] or pets[h][w].count() or people[h][w].count()) {
        return false;
    }
    for (auto [dh, dw] : dir4) {
        ll nh = h+dh, nw = w+dw;
        if (nh < 0 or nw < 0 or nh >= GRID_SIZE or nw >= GRID_SIZE) continue;
        if (pets[nh][nw].count()) {
            return false;
        }
    }
    return true;
}

// 基本行動
char base_act(Pet& pet, ll i) {
    ll h = pet.h, w = pet.w;
    while (1) {
        ll d = randrange(0, 4);
        auto [dh, dw] = dir4[d];
        int nh = h+dh, nw = w+dw;
        if (nh < 0 or nw < 0 or nh >= GRID_SIZE or nw >= GRID_SIZE) continue;
        if (blocked[nh][nw]) continue;
        // この行動に確定
        pets[pet.h][pet.w].reset(i);
        pet.h += dh, pet.w += dw;
        pets[pet.h][pet.w].set(i);
        return UDLR[d];
    }
}

// 最終スコア計算
ld calc_score(vector<Human>& H) {
    ll M = H.size();
    ld res = 0;
    rep(i, M) {
        auto [ri, ni] = bfs(H[i].h, H[i].w);
        res += ri/900.0*pow(2.0, -ni);
    }
    return round(1e8*res/M);
}

ld solve(int testcase=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            exit(0);
        }
    #endif
    ll N, M;
    cin >> N;
    vector<Pet> P(N);
    rep(i, N) {
        cin >> P[i].h >> P[i].w >> P[i].type;
        P[i].h--; P[i].w--;
        pets[P[i].h][P[i].w].set(i);
    }
    cin >> M;
    vector<Human> H(M);
    rep(i, M) {
        cin >> H[i].h >> H[i].w;
        H[i].h--; H[i].w--;
        people[H[i].h][H[i].w].set(i);
    }
    #ifdef __LOCAL
        ll seed;
        cin >> seed;
    #endif

    rep(_, TURN_COUNT) {
        // Human's action
        // ".": none, "udlr": block, "UDLR": move
        string action(M, '.');
        rep(i, M) {
            ll h = H[i].h, w = H[i].w;
            rep(d, 4) {
                auto [dh, dw] = dir4[d];
                ll nh = h+dh;
                ll nw = w+dw;
                // まずはひたすら周囲に壁作るだけ
                if (can_block(nh, nw)) {
                    blocked[nh][nw] = true;
                    action[i] = udlr[d];
                    break;
                }
            }
        }
        #ifdef __LOCAL
            ofs << action << endl;
        #else
            cout << action << endl;
        #endif

        // Pets' action
        rep(i, N) {
            #ifdef __LOCAL
                // ペットの行動をシミュレート
                action = "";
                // 犬・猫はとりあえず面倒なので仮で2回行動
                if (P[i].type >= 4) {
                    rep(_, 2) action += base_act(P[i], i);
                // 他はタイプ番号 = 行動回数でOK
                } else {
                    rep(_, P[i].type) action += base_act(P[i], i);
                }
                ofs << action;
                if (i != N-1) ofs << ' ';
                else ofs << endl;
            #else
                cin >> action;
                pets[P[i].h][P[i].w].reset(i);
                for (auto c : action) {
                    auto [dh, dw] = dir4[UDLRrev[c]];
                    P[i].h += dh;
                    P[i].w += dw;
                }
                pets[P[i].h][P[i].w].set(i);
            #endif
        }
    }

    ld score = calc_score(H);
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            0,
        };
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
        ld score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}
