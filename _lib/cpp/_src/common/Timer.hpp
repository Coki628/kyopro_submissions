#include "../base.hpp"

// 環境に依存せずミリ秒単位で時間取得するクラス
struct Timer {

    chrono::_V2::system_clock::time_point start_time;
    
    // 初期化時に時間計測を開始
    Timer() {
        start_time = this->now();
    }

    chrono::_V2::system_clock::time_point now() {
        return chrono::high_resolution_clock::now();
    }

    // 経過時間
    int64_t get_elapse() {
        return chrono::duration_cast<chrono::milliseconds>(this->now() - start_time).count();
    }
};
