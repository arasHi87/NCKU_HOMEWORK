#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bitmap {
    int *bits, range;
} Bitmap;

int _h;

Bitmap* BMapInit(int range)
{
    Bitmap* bm = (Bitmap*)malloc(sizeof(Bitmap));
    bm->bits = (int*)malloc(sizeof(int) * range + 1);
    bm->range = range;
    memset(bm->bits, 0, sizeof(bm->range));
    return bm;
}

void BMapSet(Bitmap* bm, int x)
{
    bm->bits[(x % bm->range)] |= (1 << (x % 32));
}

int BMapExist(Bitmap* bm, int x)
{
    return (bm->bits[(x % bm->range)] & (1 << (x % 32))) != 0;
}

int murmurhash(char* key, int len, int seed)
{
    const int m = 0x1b873593;
    const int r = 47;

    uint64_t h = seed ^ (len * m);

    const uint64_t* data = (const uint64_t*)key;
    const uint64_t* end = data + (len / 8);

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const uint8_t* data2 = (const uint8_t*)data;

    switch (len & 7) {
    case 7:
        h ^= ((uint64_t)data2[6]) << 48;
    case 6:
        h ^= ((uint64_t)data2[5]) << 40;
    case 5:
        h ^= ((uint64_t)data2[4]) << 32;
    case 4:
        h ^= ((uint64_t)data2[3]) << 24;
    case 3:
        h ^= ((uint64_t)data2[2]) << 16;
    case 2:
        h ^= ((uint64_t)data2[1]) << 8;
    case 1:
        h ^= ((uint64_t)data2[0]);
        h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h % 2147483647;
}

void BFilterSet(Bitmap* bm, char* str)
{
    for (int i = 1; i <= _h; i++) {
        BMapSet(bm, (murmurhash(str, strlen(str), 1 << i)));
    }
}

int BFilterExist(Bitmap* bm, char* str)
{
    int tmp = 0;
    for (int i = 1; i <= _h; i++) {
        if (!BMapExist(bm, (murmurhash(str, strlen(str), 1 << i))))
            return 0;
    }
    return 1;
}

/*
M = 100000
N = 10000
U = 10000
*/

int main()
{
    int n, m;
    scanf("%d%d%d", &n, &m, &_h);

    char* str = (char*)malloc(sizeof(char) * 100);
    Bitmap* bm = BMapInit(m);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), BFilterSet(bm, str);
    for (int i = 1; i <= n; i++)
        scanf("%s", str), printf("%d\n", BFilterExist(bm, str));
}