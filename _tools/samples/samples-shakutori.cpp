/*
・ライブラリ：尺取りサンプル
*/

#include "macros.hpp"


// 基本形(ABC098d)
ll ans = 0, sm = 0, xsm = 0;
deque<ll> que;
for (auto a : A) {
    sm += a;
    xsm ^= a;
    que.eb(a);
    while (que.size() and sm > xsm) {
        sm -= que.front();
        xsm ^= que.front();
        que.pop_front();
    }
    ans += que.size();
}
print(ans);

// 更新処理が大きい例(cf1516_d)
vector<int> nxt(N + 1);
map<ll, ll> C;
deque<ll> que;
// 後ろから回せば左端を軸にしたい時も使える
rep(i, N - 1, -1, -1) {;
    ll ngcnt = 0;
    for (auto [k, v] : factorize(A[i])) {
        C[k]++;
        if (C[k] == 2) {
            ngcnt++;
        }
    }
    que.eb(A[i])
    while (que.size() and ngcnt > 0) {
        for (auto [k, v] : factorize(que.front())) {
            C[k]--;
            if (C[k] == 1) {
                ngcnt--;
            }
        }
        que.pop_front();
    }
    nxt[i] = i + que.size();
}
nxt[N] = N;

// 左端が一気に進むタイプ(typical90_001)
// ※これはもう尺取りじゃなくてランレングスみたいな貪欲でいい…。
// ll cur = 0, cnt = 0, r = 0;
// rep(l, N) {
//     // 右端の更新
//     while (r < N and A[r]-cur < x) {
//         r++;
//     }
//     // 答えに関係する処理
//     if (r < N) {
//         cnt++;
//         cur = A[r];
//     }
//     // 左端の更新
//     l = r;
// }

// フラグ持ってやってみた版(typical90_001)
// ※これはもう尺取りじゃなくてランレングスみたいな貪欲でいい…。
// ll cur = 0, cnt = 0, r = 0;
// rep(l, N) {
//     // 右端の更新
//     bool ok = 1;
//     while (r < N and ok) {
//         ok = A[r]-cur < x;
//         if (ok) {
//             r++;
//         }
//     }
//     // 答えに関係する処理
//     if (r < N) {
//         cnt++;
//         cur = A[r];
//     }
//     // 左端の更新
//     l = r;
// }

// (typical90_034)
map<ll, ll> C;
ll ans = 0, cnt = 0;
deque<ll> que;
for (auto a : A) {
    if (C[a] == 0) {
        cnt++;
    }
    C[a]++;
    que.eb(a);
    while (que.size() and cnt > K) {
        C[que.front()]--;
        if (C[que.front()] == 0) {
            cnt--;
        }
        que.pop_front();
    }
    chmax(ans, (ll)que.size());
}
print(ans);

// なるべく短く動かすタイプ(DSL_3_B)
deque<ll> que;
vector<ll> C(K + 1);
ll ans = INF, cnt = 0, i = 0;
rep(_, N) {
    while (i < N and cnt < K) {
        que.eb(A[i]);
        if (A[i] <= K) {
            C[A[i]]++;
            if (C[A[i]] == 1) {
                cnt++;
            }
        }
        i++;
    }
    // 満たしてると限らないので条件チェックする
    if (cnt == K) {
        chmin(ans, (ll)que.size());
    }
    if (que.front() <= K) {
        C[que.front()]--;
        if (C[que.front()] == 0) {
            cnt--;
        }
    }
    que.pop_front();
}
if (ans >= INF) {
    ans = 0;
}
print(ans);

// これもなるべく短く動かすタイプ。
// 集合管理で、区間の外側同士が条件を満たすので、集合を2つ持つ(ABC215_f)
BIT<ll> bitl(M), bitr(M);
deque<ll> quel, quer;
rep(i, N) {
    bitr.add(cpy[i], 1);
    quer.eb(i);
}
rep(i, N) {
    // 左集合に1個詰める
    bitl.add(cpy[i], 1);
    quel.eb(i);
    // 空になるか条件を満たすまで右集合から取り除く
    while (quer.size() and X[quer.front()] - X[quel.back()] < k) {
        bitr.add(cpy[quer.front()], -1);
        quer.pop_front();
    }
    if (quer.size()) {
        ll bitlmn = cp.unzip(bitl.bisearch_fore(0, M - 1, 1));
        ll bitlmx = cp.unzip(bitl.bisearch_back(0, M - 1, 1));
        ll bitrmn = cp.unzip(bitr.bisearch_fore(0, M - 1, 1));
        ll bitrmx = cp.unzip(bitr.bisearch_back(0, M - 1, 1));
        if (bitlmx - bitrmn >= k or bitrmx - bitlmn >= k) {
            return true;
        }
    } else {
        break;
    }
}
return false;

// 右端固定で左端を動かすタイプ(typical90_089)
deque<ll> que;
ll inv = 0;
BIT<mint> dp(N + 1);
dp.add(0, 1);
rep(i, N) {
    inv += bit.query(A[i] + 1, M);
    bit.add(A[i], 1);
    que.pb(i);
    while (que.size() and inv > K) {
        inv -= bit.query(0, A[que.front()]);
        bit.add(A[que.front()], -1);
        que.pop_front();
    }
    assert(que.size());
    ll j = que.front();
    dp.add(i + 1, dp.query(j, i + 1));
}
mint ans = dp[N];
print(ans);

// ソートして縦を尺取り、横を遅延セグ木で管理みたいなやつ(cf1555_e)
sort(ALL(WLR));
auto [W, L, R] = zip(WLR);
auto seg = get_lazy_segment_tree(vector<ll>(M - 1, 0), f, g, h, T, E);
deque<ll> que;
ll ans = INF, i = 0;
rep(_, N) {
    while (i < N and seg.query(0, M - 1) == 0) {
        seg.update(L[i], R[i], 1);
        que.pb(i);
        i++;
    }
    if (seg.query(0, M - 1) > 0) {
        chmin(ans, W[que.back()] - W[que.front()]);
    }
    seg.update(L[que.front()], R[que.front()], -1);
    que.pop_front();
}
assert(ans < INF);
print(ans);

// これも内側でセグ木を判定に使うタイプ(iroha2019day1l)
deque<ll> que;
ll cnt = 0, i = 0;
rep(_, N) {
    while (i < N and st.query(i - que.size(), i) < x) {
        que.pb(A[i]);
        i++;
    }
    if (st.query(i - que.size(), i) >= x) {
        cnt += N - i + 1;
    }
    que.pop_front();
}
return cnt >= K;

// ある区間長wlenに収まる区間の最大個数。
// wlenより長い区間を予め省くことで、尺取りパートはシンプルに済むようになっている。(joig2021_f)
ll wlen = S / (dh - uh);
vector<pll> vec;
rep(i, M) {
    if (U[i] >= uh and D[i] < dh and R[i] - L[i] + 1 <= wlen) {
        vec.eb(L[i], 0);
        vec.eb(R[i], 1);
    }
}
ll m = vec.size();
sort(ALL(vec));

deque<ll> que;
ll res = 0, cnt = 0;
rep(i, m) {
    auto [val, lr] = vec[i];
    if (lr == 1) {
        cnt++;
    }
    que.eb(i);
    while (que.size() and vec[que.back()].first - vec[que.front()].first + 1 > wlen) {
        if (vec[que.front()].second == 0) {
            cnt--;
        }
        que.pop_front();
    }
    chmax(res, cnt);
}
chmin(ans, M - res);
