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
- Memory overhead per entry is 12B + size of the key
- Iteration:
    - faster than iterating over maps
    - is a bit dependent on the order of element removal tho
        - large pool, with removed items in the middle still has to iterate over the entire range
        - shouldn't be problematic with regular inserts tho

\* - key is necessary, in order to distinguish different elements reusing the same slot (for example after calling *insert, remove, insert* - same slot now has different element)

## Benchmark results:

benchmark name            | vector         | pool           | map            | un_map         |  CHECKSUM     |
------------------------- | -------------- | -------------- | -------------- | -------------- | --------------|
Insert                    |         0.59ms |         3.29ms |        10.12ms |         7.25ms |       Y       |
Insert+Delete             |         0.47ms |         1.05ms |        36.08ms |        10.94ms |       Y       |
Iteration (14)            |         0.27ms |         1.29ms |         3.98ms |         0.50ms |       Y       |
Iteration (250)           |         3.28ms |        15.24ms |        89.84ms |        23.77ms |       Y       |
Iteration (24000)         |       329.66ms |      1564.53ms |     12684.17ms |      6192.08ms |       Y       |
Iteration (fragmented)    |       161.02ms |      1678.74ms |      8146.12ms |      4917.81ms |       Y       |
Iteration (24000, r=0.10) |        28.30ms |       129.91ms |       995.85ms |       562.71ms |       Y       |
Iteration (24000, r=0.25) |        71.05ms |       324.40ms |      2877.34ms |      1414.62ms |       Y       |
Iteration (24000, r=0.50) |       161.03ms |       731.49ms |      6196.29ms |      3233.52ms |       Y       |
Iteration (24000, r=0.75) |       252.56ms |      1097.11ms |      9501.16ms |      4743.60ms |       Y       |
------------------------- | -------------- | -------------- | -------------- | -------------- | --------------|
Times are in [ms]
rep count: 100000

