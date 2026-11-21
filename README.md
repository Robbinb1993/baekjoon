# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).
Each problem has a standalone solution, with the problem number at the start of its filename.

| Problem | Solution | Approach |
| --- | --- | --- |
| 1602 | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time |
| 1648 | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings |
| 2873 | [Roller Coaster](2873_rollercoaster.cc) | Construct a zigzag path based on grid parity |
| 2887 | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm |
| 3015 | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights |
| 3197 | [Swan Lake](3197_swan_lake.cc) | Melt ice day by day and track connected water with Union-Find |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
