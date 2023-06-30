#include <stdio.h>

#include "bench_defs.h"

#define USE_VEC     1
#define USE_POOL    2
#define USE_MAP     4
#define USE_UNMAP   8

#define HAS_FLAG(x, f) (((x) & (f)) == f)

#define NUM_SHORT 14
#define NUM_MID 250
#define NUM_LONG 24000

template<typename bench>
void run_bench(bench& b, int repCount);

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Specify which container to use (bitmap - 2^0=vector, 2^1=pool, 2^2=map, 2^3=unordered_map)\n");
        return 1;
    }

    int repCount = int(1e5);
    int ctype = std::stoi(argv[1]);

    if(HAS_FLAG(ctype, USE_VEC)) {
        vec_bench b;
        run_bench<vec_bench>(b, repCount);
    }

    if(HAS_FLAG(ctype, USE_POOL)) {
        pool_bench b;
        run_bench<pool_bench>(b, repCount);
    }

    if(HAS_FLAG(ctype, USE_MAP)) {
        map_bench b;
        run_bench<map_bench>(b, repCount);
    }

    if(HAS_FLAG(ctype, USE_UNMAP)) {
        umap_bench b;
        run_bench<umap_bench>(b, repCount);
    }

    return 0;
}

template<typename bench>
void run_bench(bench& b, int repCount) {
    Timer timer;
    long long time = 0;
    long long sum = 0;

    printf("======= %s =======\n\t%ld reps\n", b.name(), repCount);

    printf("=== Insert ===\n");
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.insert(i, i);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    b.checksum();

    printf("=== Insert+Delete ===\n");
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.insert(i, i);
        b.remove(i);
        b.insert(i, i);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    b.checksum();

    printf("=== Iteration (%d) ===\n", NUM_SHORT);
    b.reset();
    for(int i = 0; i < NUM_SHORT; i++)
        b.insert(i, i);
    sum = 0;
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.sum(sum);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    printf("checksum: %llu\n\n", sum);
    b.clear();

    printf("=== Iteration (%d) ===\n", NUM_MID);
    b.reset();
    for(int i = 0; i < NUM_MID; i++)
        b.insert(i, i);
    sum = 0;
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.sum(sum);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    printf("checksum: %llu\n\n", sum);
    b.clear();

    printf("=== Iteration (%d) ===\n", NUM_LONG);
    b.reset();
    for(int i = 0; i < NUM_LONG; i++)
        b.insert(i, i);
    sum = 0;
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.sum(sum);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    printf("checksum: %llu\n\n", sum);
    b.clear();

    printf("=== Iteration (fragmented) ===\n", NUM_LONG);
    b.reset();
    for(int i = 0; i < NUM_LONG; i++)
        b.insert(i, i);
    for(int i = NUM_LONG-2-1; i >= 0; i -= 4) {
        b.remove(i+1);
        b.remove(i);
    }
    sum = 0;
    timer.Reset();
    for(int i = 0; i < repCount; i++) {
        b.sum(sum);
    }
    time = timer.TimeElapsed<Timer::us>();
    printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
    printf("checksum: %llu\n\n", sum);
    b.clear();

    for(int k = 0; k < 4; k++) {
        float f = int(k==0)*0.1f + int(k!=0) * 0.25f * (k);
        int fill = int(NUM_LONG * f);
        printf("=== Iteration (%d, r=%.2f) ===\n", NUM_LONG, f);
        b.reset();
        for(int i = 0; i < NUM_LONG; i++)
            b.insert(i, i);
        b.clear();
        for(int i = 0; i < fill; i++)
            b.insert(i, i);
        sum = 0;
        timer.Reset();
        for(int i = 0; i < repCount; i++) {
            b.sum(sum);
        }
        time = timer.TimeElapsed<Timer::us>();
        printf("Time elapsed: %.2fms (1 rep ~= %lldus)\n", time * 1e-3f, time / repCount);
        printf("checksum: %llu\n\n", sum);
        b.clear();
    }

    printf("==Done==\n");
}
