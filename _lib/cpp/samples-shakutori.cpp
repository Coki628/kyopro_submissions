/*
・ライブラリ：尺取りサンプル
*/

#include "macros.hpp"


// 基本形(ABC098d)
ll r = 0, sm = 0, xsm = 0, ans = 0;
rep(l, N) {
    // 右端の更新
    while (r < N and sm+A[r] == (xsm^A[r])) {
        sm += A[r];
        xsm ^= A[r];
        r++;
    }
    // 答えに関係する処理
    ans += r-l;
    // 左端の更新
    sm -= A[l];
    xsm ^= A[l];
}


// 更新処理が大きいのでフラグを使った例(cf1516_d)
ll r = 0;
set<ll> se;
vector<ll> B(N+1);
rep(l, N) {
    // 右端の更新
    bool ok = 1;
    while (r < N and ok) {
        auto fact = factorize(A[r]);
        for (auto [k, v] : fact) {
            if (se.count(k)) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            for (auto [k, v] : fact) {
                se.insert(k);
            }
            r++;
        }
    }
    // 答えに関係する処理
    B[l] = r;
    // 左端の更新
    auto fact = factorize(A[l]);
    for (auto [k, v] : fact) {
        se.erase(k);
    }
}
B[N] = N;


// 左端が一気に進むタイプ(typical90_001)
ll cur = 0, cnt = 0, r = 0;
rep(l, N) {
    // 右端の更新
    while (r < N and A[r]-cur < x) {
        r++;
    }
    // 答えに関係する処理
    if (r < N) {
        cnt++;
        cur = A[r];
    }
    // 左端の更新
    l = r;
}


// フラグ持ってやってみた版(typical90_001)
ll cur = 0, cnt = 0, r = 0;
rep(l, N) {
    // 右端の更新
    bool ok = 1;
    while (r < N and ok) {
        ok = A[r]-cur < x;
        if (ok) {
            r++;
        }
    }
    // 答えに関係する処理
    if (r < N) {
        cnt++;
        cur = A[r];
    }
    // 左端の更新
    l = r;
}


// 区間長0の操作付き(今回いらなかったけど。。)(typical90_034)
ll r = 0, ans = 0;
map<ll, ll> C;
rep(l, N) {
    // 右端の更新
    while (r < N and (C.count(A[r]) or C.size() < K)) {
        C[A[r]]++;
        r++;
    }
    // 答えに関係する処理
    chmax(ans, r-l);
    // 区間長0
    if (l == r) {
        r++;
    } else {
        // 左端の更新
        C[A[l]]--;
        if (C[A[l]] == 0) C.erase(A[l]);
    }
}


// なるべく短く動かすタイプ(DSL_3_B)
ll r = 0, ans = INF;
map<ll, ll> mp;
rep(l, N) {
    bool ok = 0;
    while (r < N and mp.size() < K) {
        if (A[r] <= K) {
            mp[A[r]]++;
        }
        r++;
    }
    if (mp.size() == K) {
        chmin(ans, r-l);
    }
    if (A[l] <= K) {
        mp[A[l]]--;
        if (mp[A[l]] == 0) mp.erase(A[l]);
    }
}

// これもなるべく短く動かすタイプ。
// 集合管理で、区間の外側同士が条件を満たすので、集合を2つ持つ(ABC215_f)
BIT<int> bit1(M), bit2(M);
bit1.add(Y[0], 1);
rep(i, 1, N) bit2.add(Y[i], 1);
int r = 1;
rep(l, N) {
    while (r < N and X[r]-X[l] < m) {
        bit2.add(Y[r], -1);
        r++;
    }
    if (r == N) break;
    int mn1 = bit1.bisearch_fore(0, M-1, 1);
    int mx1 = bit1.bisearch_back(0, M-1, 1);
    int mn2 = bit2.bisearch_fore(0, M-1, 1);
    int mx2 = bit2.bisearch_back(0, M-1, 1);
    if (
        X[r]-X[l] >= m and mn1 != -1 and mn2 != -1 and
        (cp.unzip(mx1)-cp.unzip(mn2) >= m or cp.unzip(mx2)-cp.unzip(mn1) >= m)
    ) {
        return true;
    }
    if (l+1 < N) bit1.add(Y[l+1], 1);
}

// 右端固定で左端を動かすタイプ(typical90_089)
BIT<mint> dp(N+1);
dp.add(0, 1);
ll inv = 0, l = 0;
bit.add(A[0], 1);
rep(r, 1, N+1) {
    // 条件を満たさない間、左端を縮める
    while (l < N and inv > K) {
        inv -= bit.query(0, A[l]);
        bit.add(A[l], -1);
        l++;
    }
    dp.add(r, dp.query(l, r));
    // rep(k, l, r) {
    //     dp[r] += dp[k];
    // }
    if (r < N) {
        inv += bit.query(A[r]+1, M);
        bit.add(A[r], 1);
    }
}
mint ans = dp[N];

// ソートして縦を尺取り、横を遅延セグ木で管理みたいなやつ(cf1555_e)
ll j = 0, ans = INF;
rep(i, N) {
    while (j < N and seg.query(0, M) == 0) {
        seg.update(L[j], R[j], 1);
        j++;
    }
    if (seg.query(0, M) > 0) chmin(ans, W[j-1]-W[i]);
    seg.update(L[i], R[i], -1);
}
print(ans);

// これも内側でセグ木を判定に使うタイプ(iroha2019day1l)
auto seg = get_segment_tree([](ll a, ll b) { return a|b; }, 0LL);
seg.build(A);
ll r = 1, cnt = 0;
rep(l, N) {
    while (r <= N and seg.query(l, r) < x) {
        r++;
    }
    if (seg.query(l, r) >= x) cnt += N-r+1;
}
return cnt >= K;

// ある区間長wlenに収まる区間の最大個数。
// wlenより長い区間を予め省くことで、尺取りパートはシンプルに済むようになっている。(joig2021_f)
ll wlen = S/(dh-uh);
vector<ll> vl, vr;
rep(i, M) {
    if (U[i] >= uh and D[i] < dh and R[i]-L[i]+1 <= wlen) {
        vl.eb(L[i]);
        vr.eb(R[i]+1);
    }
}
ll n = vl.size();
sort(ALL(vl));
sort(ALL(vr));
ll r = 0, res = 0;
rep(l, n) {
    while (r < n and vr[r]-vl[l] <= wlen) {
        r++;
    }
    if (vr[r-1]-vl[l] <= wlen) {
        chmax(res, r-l);
    }
}
chmin(ans, M-res);
