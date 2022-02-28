/*
・ペットが多い時に逆に閉じ込めるようにしてみた。
　あんまり効果なし。。
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
#include "common/chmax.hpp"

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
array<ll, 3> bfs(ll sh, ll sw) {
    auto visited = list2d(GRID_SIZE, GRID_SIZE, false);
    queue<pii> que;
    que.push({sh, sw});
    array<ll, 3> res = {0, 0, 0};
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        res[0]++;
        res[1] += pets[h][w].count();
        res[2] += people[h][w].count();
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
        auto [ri, ni, _] = bfs(H[i].h, H[i].w);
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
    string action(M, '.');
    rep(i, M) {
        cin >> H[i].h >> H[i].w;
        people[H[i].h][H[i].w].set(i);
    }
    #ifdef __LOCAL
        ll seed;
        cin >> seed;
    #endif

    // 人の移動
    auto move_human = [&](Human& human, ll i, char c) -> void {
        action[i] = c;
        people[human.h][human.w].reset(i);
        auto [dh, dw] = dir4[UDLRrev[c]];
        human.h += dh, human.w += dw;
        people[human.h][human.w].set(i);
    };
    // ブロック
    auto block = [&](ll h, ll w, ll i, char c) -> void {
        action[i] = c;
        auto [dh, dw] = dir4[udlrrev[c]];
        blocked[h+dh][w+dw] = true;
    };

    vector<ll> phase(M);
    vector<bool> done(GRID_SIZE), used(GRID_SIZE), down(M);
    ll mxdoneh = 0;
    rep(turn, TURN_COUNT, 0, -1) {
        // Human's action
        // ".": none, "udlr": block, "UDLR": move
        action.assign(M, '.');
        rep(i, M) {
            ll h = H[i].h, w = H[i].w;
            // まず左上へ集合
            if (phase[i] == 0) {
                // mod 4で0の行は壁になるので早く逃げる
                if (w > 1 and h%4 == 0) {
                    move_human(H[i], i, 'U');
                } elif (w > 1 and not blocked[h][w-1]) {
                    move_human(H[i], i, 'L');
                } elif (h > 1 and not blocked[h-1][w]) {
                    move_human(H[i], i, 'U');
                } else {
                    phase[i]++;
                }
            // 進む行を探す
            } elif (phase[i] == 1) {
                // この行を進むと決める
                if (h%4 == 1 and not done[h+1]) {
                    done[h+1] = true;
                    chmax(mxdoneh, h+1);
                    move_human(H[i], i, 'R');
                    phase[i]++;
                // 次の行を見にいく
                } elif (h+1 <= 30 and turn >= TURN_COUNT/2) {
                    move_human(H[i], i, 'D');
                // 全行終わったor時間が少なくなってきた
                } else {
                    phase[i] = 4;
                }
            // 上を埋めながら行を進む
            } elif (phase[i] == 2) {
                if (can_block(h-1, w) and h%4 == 1) {
                    block(h, w, i, 'u');
                } elif (blocked[h-1][w] or h%4 != 1) {
                    // 右端まで
                    if (w == 30) {
                        move_human(H[i], i, 'D');
                        if ((h+1)%4 == 3 or h+1 == 30) {
                            phase[i]++;
                        }
                    } else {
                        move_human(H[i], i, 'R');
                    }
                }
            // 下を埋めながら左端に戻る
            } elif (phase[i] == 3) {
                if (can_block(h+1, w)) {
                    block(h, w, i, 'd');
                } elif (blocked[h+1][w]) {
                    // 左端まで
                    move_human(H[i], i, 'L');
                    if (w-1 == 1) {
                        // 時間がなくなったらこの行を強制的に閉じにいく
                        if (turn <= 5) {
                            move_human(H[i], i, 'R');
                            move_human(H[i], i, 'U');
                            phase[i] = 5;
                        } else {
                            phase[i] = 1;
                        }
                    }
                }
            // ペットがいる行を探す
            } elif (phase[i] == 4) {
                // mod 4 で 2
                if (done[h] and not used[h]) {
                    blocked[h-1][w] = true;
                    blocked[h][w] = true;
                    blocked[h+1][w] = true;
                    auto [cellcnt, petcnt, mancnt] = bfs(h, w+1);
                    blocked[h-1][w] = false;
                    blocked[h][w] = false;
                    blocked[h+1][w] = false;
                    // ペットがいない行or残りターンが少ないなら入る
                    if (
                        petcnt == 0 or
                        petcnt <= 1 and turn < 80 or
                        petcnt <= 2 and turn < 50 or
                        turn < 20
                    ) {
                        used[h] = true;
                        move_human(H[i], i, 'R');
                        phase[i]++;
                        continue;
                    }
                    // 逆にペットが多い時はペットを閉じ込める
                    if (
                        petcnt >= N/3 and mancnt <= 0
                    ) {
                        used[h] = true;
                        move_human(H[i], i, 'R');
                        phase[i] = 7;
                        continue;
                    }
                }
                // 他の行を探す
                if (h <= 2) {
                    down[i] = true;
                    move_human(H[i], i, 'D');
                } elif (h >= min(mxdoneh, 30LL)) {
                    down[i] = false;
                    move_human(H[i], i, 'U');
                } else {
                    move_human(H[i], i, down[i] ? 'D' : 'U');
                }
            // 行に入ってできるだけ早く左を閉じる
            } elif (phase[i] == 5) {
                if (w > 2 and can_block(h, w-1)) {
                    block(h, w, i, 'l');
                    phase[i]++;
                } elif (w+1 <= 30) {
                    move_human(H[i], i, 'R');
                }
            // できるだけ早く上下も閉じる
            } elif (phase[i] == 6) {
                if (can_block(h+1, w)) {
                    block(h, w, i, 'd');
                } elif (can_block(h-1, w)) {
                    block(h, w, i, 'u');
                }
                if (blocked[h+1][w] and blocked[h-1][w]) {
                    phase[i] = INF;
                }
            // ペットをこの行に閉じ込める
            } elif (phase[i] == 7) {
                // 閉じ込め終わったら探索を再開
                if (blocked[h+1][w] and blocked[h-1][w] and blocked[h][w+1]) {
                    move_human(H[i], i, 'L');
                    phase[i] = 4;
                } elif (can_block(h+1, w)) {
                    block(h, w, i, 'd');
                } elif (can_block(h-1, w)) {
                    block(h, w, i, 'u');
                } elif (can_block(h, w+1)) {
                    block(h, w, i, 'r');
                }
            // 待機
            } else {
            }
        }
        rep(i, M) {
            ll h = H[i].h, w = H[i].w;
            // 他の人が閉じてくれた
            if (phase[i] == 3 and (used[h-1] or h == 30 and used[h])) {
                move_human(H[i], i, 'R');
                action[i] = '.';
                phase[i] = INF;
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
