
/*
https://www.cnblogs.com/wyb-sen/p/14400359.html
*/

long long integer_chunk_max_floor(long long n, long long i) {
    // 整除分块, 返回最大的 i', 使得 n / i' =  n / i
    return n / (n / i);
}

long long integer_chunk_min_floor(long long n, long long i) {
    // 整除分块，返回最小的 i'，使得 n / i' = n / i
    long long q = n / i;
    return (n / (q + 1)) + 1;
}

long long integer_chunk_max_ceil(long long n, long long i) {
    // 整除分块，返回最大的 i' 使得向上取整相等: ceil(n / i') = ceil(n / i)
    if (i == n) return n;
    long long t = (n + i - 1) / i;
    return (n + t - 2) / (t - 1) - 1;
}

long long integer_chunk_min_ceil(long long n, long long i) {
    // 整除分块，返回最小的 i' 使得向上取整相等: ceil(n / i') = ceil(n / i)
    long long t = (n + i - 1) / i + 1;
    return (n + t - 2) / (t - 1);
}
