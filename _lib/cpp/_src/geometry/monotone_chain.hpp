#include "../macros.hpp"
#include "Point.hpp"

// アンドリューのアルゴリズム(Monotone Chain)：凸包に使った座標と距離を返す
template<typename T>
vector<pair<Point<T>, ld>> monotone_chain(vector<Point<T>> li) {
    int N = li.size();
    assert(N >= 2);

    sort(ALL(li), [](Point<T> a, Point<T> b) {
        // ソート条件にyも使う
        if (a.x == b.x) return a.y < b.y;
        else return a.x < b.x; 
    });

    // 上半分
    // 使う座標と距離を保持
    vector<pair<Point<T>, ld>> stack;
    stack.pb({li[0], 0});
    stack.pb({li[1], li[0].abs(li[1])});
    rep(i, 2, N) {
        // 1つ前->次 と 1つ前->2つ前 のベクトルで外積をチェックして向きを判定する
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            // 次が反時計回り側にある時は1つ前を外す
            stack.pop_back();
        }
        // 次が時計回り側にあればOKなので進める
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    vector<pair<Point<T>, ld>> res;
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }

    // 下半分(やることは同じ)
    stack.clear();
    stack.pb({li[li.size()-1], 0});
    stack.pb({li[li.size()-2], li[li.size()-1].abs(li[li.size()-2])});
    rrep(i, N-3, -1) {
        while (stack.size() >= 2 and ccw(stack[stack.size()-2].first, stack[stack.size()-1].first, li[i]) == 1) {
            stack.pop_back();
        }
        stack.pb({li[i], stack.back().first.abs(li[i])});
    }
    rep(i, 1, stack.size()) {
        res.pb(stack[i]);
    }
    return res;
}
