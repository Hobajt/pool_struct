# Pool data structure

Custom data structure that I've built.

## Features:
- It's essentially a vector + stack that tracks unused places in the vector.
- Insert, remove and access are O(1)
- Doesn't respect order of elements - elements are inserted into empty slots, not at the end
- Insert can cause reallocation - doesn't preserve pointers
- Element addressing:
    - insert requires a unique identifier - key\* (sort of like a key in std::map)
    - elements can be accessed through their index (O(1)) or by their key (O(n))
    - remove operation doesn't change positions of other elements
- Memory overhead per entry is ...
- Iteration isn't ideal, as the entire pool needs to be iterated (including empty slots)
    - complexity is dependent on capacity, not size
    - is still faster than iterating maps (with reasonable size/capacity ratio ~0.3 & higher)

\* - key is necessary, in order to distinguish different elements reusing the same slot (for example after calling *insert, remove, insert* - same slot now has different element)

## Benchmark results:
```           ---            | vector         | pool           | map            | un_map         |  CHECKSUM     |
------------------------- | -------------- | -------------- | -------------- | -------------- | --------------|
Insert                    |         0.60ms |         2.36ms |        10.17ms |         8.03ms |       Y       |
Insert+Delete             |         0.46ms |         0.56ms |        36.66ms |        11.84ms |       Y       |
Iteration (14)            |         0.27ms |         0.74ms |         4.11ms |         0.48ms |       Y       |
Iteration (250)           |         3.30ms |        12.50ms |        91.98ms |        25.89ms |       Y       |
Iteration (24000)         |       319.53ms |      2083.63ms |     12451.67ms |      6645.71ms |       Y       |
Iteration (fragmented)    |       156.01ms |      2254.45ms |      8282.87ms |      5116.84ms |       Y       |
Iteration (24000, r=0.10) |        30.16ms |      1885.66ms |      1047.11ms |       595.93ms |       Y       |
Iteration (24000, r=0.25) |        75.46ms |      1881.17ms |      2959.71ms |      1386.36ms |       Y       |
Iteration (24000, r=0.50) |       158.04ms |      1855.81ms |      6432.09ms |      3361.31ms |       Y       |
Iteration (24000, r=0.75) |       236.11ms |      1926.28ms |      9534.95ms |      5288.90ms |       Y       |
------------------------- | -------------- | -------------- | -------------- | -------------- | --------------|
Times are in [ms]
rep count: 100000
```