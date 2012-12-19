#include <cstdio>


#define MAXLEN 1000000


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    void next(char *s, int &l) {
        l = 0; for (skip(); b > 32; read()) *s++ = b, ++l; *s = 0; }
};

#define MAXS MAXLEN
#define MAXW MAXLEN
struct KMP {
    char S[MAXS + 1], W[MAXW + 1]; int ls, lw; int T[MAXW + 1];
    void init() {
        T[0] = -1, T[1] = 0;
        for (int p=2,c=0; p < lw;) {
            if (W[p-1] == W[c]) T[p++] = ++c;
            else if (c > 0) c = T[c];
            else T[p++] = 0;
        }
    }
    int search() {
        int cnt = 0;
        for (int m=0, i=0; m + i < ls;) {
            if (W[i] == S[m + i]) {
                if (i == lw - 1) {
                    ++cnt;
                    m += i - T[i];
                    i = T[i];
                }
                else
                    ++i;
            }
            else { m += i - T[i]; i = T[i] >= 0 ? T[i] : 0; }
        }
        return cnt;
    }
};


KMP kmp;


int solve()
{
    if (kmp.lw > kmp.ls) return 0;

    kmp.init();
    return kmp.search();
}

int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        rr.next(kmp.S, kmp.ls);
        rr.next(kmp.W, kmp.lw);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
