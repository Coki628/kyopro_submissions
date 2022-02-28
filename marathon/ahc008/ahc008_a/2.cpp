/*
・やっと作れた次の段階。細い道作って、中にペットが居なくなった所で塞いで籠る。
　時間が近くなったら範囲を狭めて小さい範囲でもいいからできる限りペット0を目指す。
　これで2億5000万点くらい。
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
#include "common/ceil.hpp"

const int GRID_SIZE = 32;
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
        if (blocked[nh][nw]) continue;
        // この行動に確定
        pets[pet.h][pet.w].reset(i);
        pet.h += dh, pet.w += dw;
        pets[pet.h][pet.w].set(i);
        return UDLR[d];
    }
}

// 人の移動
void move_human(Human& human, ll i, char c) {
    people[human.h][human.w].reset(i);
    auto [dh, dw] = dir4[UDLRrev[c]];
    human.h += dh, human.w += dw;
    people[human.h][human.w].set(i);
}

// ペットの移動
void move_pet(Pet& pet, ll i, string& action) {
    pets[pet.h][pet.w].reset(i);
    for (auto c : action) {
        auto [dh, dw] = dir4[UDLRrev[c]];
        pet.h += dh;
        pet.w += dw;
    }
    pets[pet.h][pet.w].set(i);
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

    // 番兵
    rep(i, GRID_SIZE) {
        blocked[0][i] = true;
        blocked[i][0] = true;
        blocked[GRID_SIZE-1][i] = true;
        blocked[i][GRID_SIZE-1] = true;
    }

    ll N, M;
    cin >> N;
    vector<Pet> P(N);
    rep(i, N) {
        cin >> P[i].h >> P[i].w >> P[i].type;
        pets[P[i].h][P[i].w].set(i);
    }
    cin >> M;
    vector<Human> H(M);
    vector<ll> targetrow(M);
    rep(i, M) {
        cin >> H[i].h >> H[i].w;
        people[H[i].h][H[i].w].set(i);
        // 壁を作る行
        targetrow[i] = ceil(H[i].h, 2LL)*2;
    }
    #ifdef __LOCAL
        ll seed;
        cin >> seed;
    #endif

    vector<ll> phase(M);
    rep(i, M) {
        if (H[i].h == targetrow[i]) {
            phase[i]++;
            if (H[i].w == 1) {
                phase[i]++;
            }
        }
    }
    rep(turn, TURN_COUNT) {
        // Human's action
        // ".": none, "udlr": block, "UDLR": move
        string action(M, '.');
        rep(i, M) {
            ll &h = H[i].h, &w = H[i].w;
            // 縦の初期位置調整
            if (phase[i] == 0) {
                action[i] = 'D';
                move_human(H[i], i, action[i]);
                phase[i]++;
                if (w == 1) {
                    phase[i]++;
                }
            // 左端へ移動
            } elif (phase[i] == 1) {
                action[i] = 'L';
                move_human(H[i], i, action[i]);
                if (w == 1) {
                    phase[i]++;
                }
            // 上下をブロックしながら右移動
            } elif (phase[i] == 2) {
                if (not blocked[h-1][w] and can_block(h-1, w)) {
                    action[i] = 'u';
                    blocked[h-1][w] = true;
                } elif (not blocked[h+1][w] and can_block(h+1, w)) {
                    action[i] = 'd';
                    blocked[h+1][w] = true;
                } elif (blocked[h-1][w] and blocked[h+1][w]) {
                    // 右端手前まで
                    if (w == GRID_SIZE-3) {
                        action[i] = '.';
                        phase[i]++;
                    } else {
                        action[i] = 'R';
                        move_human(H[i], i, action[i]);
                    }
                }
            // 壁の内側にペットがいなくなったら籠る
            } elif (phase[i] == 3) {
                blocked[h][w+1] = true;
                auto [cellcnt, petcnt] = bfs(h, w);
                blocked[h][w+1] = false;
                if (petcnt == 0 and can_block(h, w+1)) {
                    action[i] = 'r';
                    blocked[h][w+1] = true;
                    phase[i]++;
                // ターンが少なくなってきたら動いて領域を狭める
                } elif (TURN_COUNT-turn < GRID_SIZE and w-1 >= 1) {
                    action[i] = 'L';
                    move_human(H[i], i, action[i]);
                } else {
                    action[i] = '.';
                }
            // やることやったので待機
            } else {
                action[i] = '.';
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
                move_pet(P[i], i, action);
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
            12,
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
