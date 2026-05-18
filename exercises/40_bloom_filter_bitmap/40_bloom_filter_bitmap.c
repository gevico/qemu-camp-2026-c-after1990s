#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 20 位图实现 Bloom 过滤器
 * 需求：m=100 位图，k=3 个哈希函数；插入 "apple"、"banana"，查询示例
 */

typedef struct {
    unsigned char *bits;
    size_t m; /* 位图大小（比特） */
} Bloom;

static Bloom *bloom_create(size_t m) {
    Bloom *bf = (Bloom *)malloc(sizeof(Bloom));
    if (!bf) return NULL;
    bf->m = m;
    bf->bits = (unsigned char *)calloc((m + 7) / 8, sizeof(unsigned char));
    if (!bf->bits) {
        free(bf);
        return NULL;
    }
    return bf;
}

static void bloom_free(Bloom *bf) {
    if (bf) {
        free(bf->bits);
        free(bf);
    }
}

/* 位操作 */
static void set_bit(unsigned char *bm, size_t idx) {
    bm[idx / 8] |= (1 << (idx % 8));
}
static int test_bit(const unsigned char *bm, size_t idx) {
    return (bm[idx / 8] >> (idx % 8)) & 1;
}

/* 三个简单哈希：sum(c*k) % m */
/**
 * @brief 使用第 k 个哈希函数计算字符串的哈希值，用于布隆过滤器
 *
 * 通过将每个字符的 ASCII 值乘以权重因子 k 并求和，再对位图大小 m 取模，
 * 实现用单一逻辑生成多个不同的哈希函数。
 *
 * @param s 待哈希的字符串
 * @param m 位图大小，哈希值取模的模数
 * @param k 哈希函数编号，作为字符权重因子以产生不同的哈希值
 * @return 字符串 s 在第 k 个哈希函数下的哈希值，范围为 [0, m-1]
 */
static size_t hash_k(const char *s, size_t m, int k) {
    size_t hash = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        hash += (unsigned char)s[i] * k;
    }
    return hash % m;
}

static void bloom_add(Bloom *bf, const char *s) {
    for (int k = 1; k <= 3; k++) {
        size_t idx = hash_k(s, bf->m, k);
        set_bit(bf->bits, idx);
    }
}

static int bloom_maybe_contains(Bloom *bf, const char *s) {
    for (int k = 1; k <= 3; k++) {
        size_t idx = hash_k(s, bf->m, k);
        if (!test_bit(bf->bits, idx)) {
            return 0; /* 一定不存在 */
        }
    }
    return 1; /* 可能存在 */
}

int main(void) {
    const size_t m = 100; /* 位图大小 */
    Bloom *bf = bloom_create(m);
    if (!bf) {
        fprintf(stderr, "bloom create failed\n");
        return 1;
    }

    /* 插入元素："apple"、"banana" */
    bloom_add(bf, "apple");
    bloom_add(bf, "banana");

    /* 查询元素："apple"（应存在）、"orange"（可能存在误判） */
    int apple = bloom_maybe_contains(bf, "apple");
    int grape = bloom_maybe_contains(bf, "grape"); /* 未插入，可能误判 */

    printf("apple exists: %d\n", apple); /* 必须为 1（无假阴性） */
    printf("grape exists: %d\n", grape); /* 允许 0 或 1（可能误判） */

    bloom_free(bf);
    return 0;
}
