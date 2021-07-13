/*
・ライブラリ：尺取りサンプル
*/

#include "_tpl.cpp"


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
