/*
・ライブラリ：幾何
*/

#include "_tpl.cpp"


// 回転行列：座標centerを軸に座標pから半時計回りにdig度回転させた座標を返す
pair<ld, ld> rotate(pair<ld, ld> center, pair<ld, ld> p, ld dig) {
    ld ansx = (p.first-center.first)*cos(radians(dig)) - (p.second-center.second)*sin(radians(dig)) + center.first;
    ld ansy = (p.first-center.first)*sin(radians(dig)) + (p.second-center.second)*cos(radians(dig)) + center.second;
    return {ansx, ansy};
}
