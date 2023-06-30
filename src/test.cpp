#include <stdio.h>

#include <string>
#include <vector>

#include "pool.hpp"

/* PROPER MOVE SEMANTICS & FORWARDING TEST (compared to std::vector) */

static int counterDtor = 0;
static int counterCtor = 0;
static int counterCopy = 0;
static int counterMove = 0;

struct Test {
    int a;
public:
    Test() : a(0) { printf("Create (default)\n"); counterCtor++; }
    Test(int a_) : a(a_) { printf("Create (%d)\n", a); counterCtor++; }

    ~Test() { printf("Destroy (%d)\n", a); a += 10; counterDtor++; }

    Test(const Test& t) noexcept { a = t.a; printf("Copy (%d)\n", a); counterCopy++; }
    Test& operator=(const Test& t) noexcept { a = t.a; printf("Copy (%d) assignemt\n", a); counterCopy++; return *this; }

    Test(Test&& t) noexcept { a = t.a; printf("Move (%d)\n", a); counterMove++; }
    Test& operator=(Test&& t) noexcept { a = t.a; printf("Move (%d) assignemt\n", a); counterMove++; return *this; }
};

void printContent(const std::vector<Test>& v) {
    printf("Content: ");
    for(const Test& t : v)
        printf("%d ", t.a);
    printf("\n");
}

void printContent(const pool<Test>& v) {
    printf("Content: ");
    for(const Test& t : v)
        printf("%d ", t.a);
    printf("\n");
}

int main(int argc, char** argv) {
    if(argc < 2) {
        printf("Specify which container to use (0=vector, 1=pool)\n");
        return 1;
    }

    int ctype = std::stoi(argv[1]);
    printf("===== num: %d ... using %s =====\n", ctype, ctype == 0 ? "vector" : "pool");

    if(ctype == 0) {
        std::vector<Test> v;

        printf("==insert==\n");
        for (int i = 0; i < 6; i++) {
            v.push_back(i);
            printf("----\n");
        }
        printf("==emplace==\n");
        for (int i = 0; i < 6; i++) {
            v.emplace_back(i);
            printf("----\n");
        }

        printContent(v);
    }
    else {
        pool<Test> v;

        printf("==insert==\n");
        for (int i = 0; i < 6; i++) {
            v.add(i+1, i);
            printf("----\n");
        }
        printf("==emplace==\n");
        for (int i = 0; i < 6; i++) {
            v.emplace(i+1, i);
            printf("----\n");
        }

        printContent(v);
    }

    printf("========\nDone.\n");
    printf("CTOR: %d, DTOR: %d, MOVE: %d, COPY: %d\n", counterCtor, counterDtor, counterMove, counterCopy);

    return 0;
}
