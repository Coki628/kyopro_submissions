// ベル数(玉区別あり、箱区別なし、制限なし) ※未Verify
ll bell(int N, int K) {
    ll ans = 0;
    rep(i, K+1) {
        ans += stirling(N, i)[N][i];
    }
    return ans;
}

// ベル数(玉区別あり、箱区別なし、制限なし) ※未Verify
mint bell(int N, int K) {

    ModTools<mint> mt(max(N, K));

    // 前計算しておく
    vector<mint> prev(K+1);
    rep(i, K+1) {
        prev[i] = (mint)1/mt.fact[i];
    }
    // 累積和
    rep(i, 1, K+1) {
        prev[i] += prev[i-1];
    }

    mint ans = 0;
    rep(i, K+1) {
        ans += (mint)pow(i, N, MOD)/mt.fact[i]*prev[K-i];
    }
    return ans;
}
