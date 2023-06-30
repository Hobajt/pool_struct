#include <stdio.h>

#include <string>
#include <vector>

#include "pool.hpp"

template <typename T, typename K = size_t>
struct pool_view {
    struct ripoff {
        using idxType = size_t;
        using keyType = K;

        struct key {
            idxType idx;
            keyType id;
        };

        struct slot {
            T data;
            key info;
            bool taken;
        };
    public:
        slot* m_data;
        idxType m_capacity;
        idxType m_size;
        idxType m_holes;
        idxType m_first;
    };

    static void print(const pool<int>& p) {
        const ripoff* rp = reinterpret_cast<const ripoff*>(&p);
        const ripoff& r = *rp;

        printf("CAP: %llu | SIZE: %llu | HOLES: %llu | FIRST: %llu\n", r.m_capacity, r.m_size, r.m_holes, r.m_first);
        printf("STACK: ");
        for(size_t i = 0; i < r.m_capacity; i++)
            printf("%3d| ", (int)r.m_data[i].info.idx);
        printf("\n");

        printf("KEYS:  ");
        for(size_t i = 0; i < r.m_capacity; i++)
            printf("%3d| ", (int)r.m_data[i].info.id);
        printf("\n");

        printf("USED:  ");
        for(size_t i = 0; i < r.m_capacity; i++)
            printf("%3d| ", (int)r.m_data[i].taken);
        printf("\n");
        printf("---------------------------\n");
    }
};

int main(int argc, char** argv) {
    using view = pool_view<int>;

    pool<int> p = pool<int>(8);
    view::print(p);

    // for(int i = 0; i < 8; i++)
    //     p.add(i, i);
    // view::print(p);

    // p.remove(0);
    // p.remove(1);

    // p.remove(6);
    // p.remove(7);

    // view::print(p);

    // p.add(69, 69);
    // view::print(p);


    for(int i = 0; i < 5; i++)
        p.add(i, i);
    view::print(p);

    printf("----------\n");

    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");

    view::print(p);
    p.remove(0);
    view::print(p);
    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");
    p.remove(3);
    view::print(p);
    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");
    p.remove(4);
    view::print(p);
    p.remove(1);
    view::print(p);
    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");

    p.add(69, 69);
    view::print(p);
    p.add(70,70);
    view::print(p);
    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");
    p.remove(2);
    view::print(p);

    printf("PRINT: ");
    for(int& v : p)
        printf("%d ", v);
    printf("\n");

    return 0;
}
