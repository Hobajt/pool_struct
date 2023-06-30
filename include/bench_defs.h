#pragma once

#include "timer.h"
#include "pool.hpp"

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

struct vec_bench {
    std::vector<int> v = {};
public:
    const char* name() const { return "vector"; }
    void insert(int idx, int value) { v.push_back(value); }
    void emplace(int idx, int value) { v.emplace_back(value); }
    void remove(int idx) { v.erase(v.begin() + idx); }
    void checksum(bool cleanup = true) { 
        long long checksum = 0;
        for(int& i : v)
            checksum += i;
        printf("checksum: %llu\n\n", checksum);

        if(cleanup)
            v.clear();
    }
    void clear() { v.clear(); }
    void reset() { v = {}; }
    void sum(long long& sum) { for(int& i : v) sum += i; }
};

struct map_bench {
    std::map<int,int> v = {};
public:
    const char* name() const { return "map   "; }
    void insert(int idx, int value) { v.insert({ idx, value }); }
    void emplace(int idx, int value) { v.emplace(idx, value); }
    void remove(int idx) { v.erase(idx); }
    void checksum(bool cleanup = true) { 
        long long checksum = 0;
        for(auto& [k, i] : v)
            checksum += i;
        printf("checksum: %llu\n\n", checksum);

        if(cleanup)
            v.clear();
    }
    void clear() { v.clear(); }
    void reset() { v = {}; }
    void sum(long long& sum) { for(auto& [k, i] : v) sum += i; }
};

struct umap_bench {
    std::unordered_map<int,int> v = {};
public:
    const char* name() const { return "un_map"; }
    void insert(int idx, int value) { v.insert({ idx, value }); }
    void emplace(int idx, int value) { v.emplace(idx, value); }
    void remove(int idx) { v.erase(idx); }
    void checksum(bool cleanup = true) { 
        long long checksum = 0;
        for(auto& [k, i] : v)
            checksum += i;
        printf("checksum: %llu\n\n", checksum);

        if(cleanup)
            v.clear();
    }
    void clear() { v.clear(); }
    void reset() { v = {}; }
    void sum(long long& sum) { for(auto& [k, i] : v) sum += i; }
};

struct pool_bench {
    pool<int> v = {};
public:
    const char* name() const { return "pool  "; }
    void insert(int idx, int value) { v.add(idx, value); }
    void emplace(int idx, int value) { v.emplace(idx, value); }
    void remove(int idx) { v.remove(idx); }
    void checksum(bool cleanup = true) { 
        long long checksum = 0;
        for(int& i : v)
            checksum += i;
        printf("checksum: %llu\n\n", checksum);

        if(cleanup)
            v.clear();
    }
    void clear() { v.clear(); }
    void reset() { v = {}; }
    void sum(long long& sum) { for(int& i : v) sum += i; }
    // void sum(long long& sum) { 
    //     for(size_t i = 0; i < v.capacity(); i++)
    //         if(v.taken(i))
    //             sum += v[i];
    // }
};