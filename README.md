# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).

| Problem | Solution | Approach |
| --- | --- | --- |
| 1006 | [Choragi the Invader](1006_choragi_the_invader.cc) | Scan the two rings column by column with bitmask DP, keeping the first column’s mask to close the loop |
| 1602 | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time |
| 1648 | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings |
| 2873 | [Roller Coaster](2873_rollercoaster.cc) | Construct a zigzag path based on grid parity |
| 2887 | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm |
| 3015 | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights |
| 3197 | [Swan Lake](3197_swan_lake.cc) | Multi-source BFS and Union-Find for incremental connectivity |
| 5719 | [Almost Shortest Path](5719_almost_shortest_path.cc) | Run Dijkstra twice, blocking every edge on any shortest path between runs |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
