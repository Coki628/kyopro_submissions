template<typename T>
T modulo(T a, T b) {
    return ((a % b) + b) % b;
}
