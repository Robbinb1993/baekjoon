# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).

| Problem | Solution | Approach | Time complexity |
| --- | --- | --- | --- |
| 1006 | [Choragi the Invader](1006_choragi_the_invader.cc) | Bitmask DP on a 2×N grid with a first-column mask for wraparound | `O(n)` |
| 1602 | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time | `O(n³ + m + q)` |
| 1648 | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings | `O(rc·2ᶜ)` |
| 1693 | [Tree Coloring](1693_tree_coloring.cc) | Tree DP with a logarithmic color bound<details><summary>Why extra colors help and how many to try</summary><p>Think bottom-up: three subtrees may be cheapest with root colors 1, 2, and 3. Giving their parent color 4 can cost less than forcing one of those subtrees to change its root color.</p><p>The tricky part is bounding the colors that the tree DP needs to try. In a minimum-cost coloring, a node of color `k` must have a neighbor of every lower color. If one is missing, recoloring the node with that color lowers the cost.</p><p>Root the tree at the node of color `k` and follow only lower colors. Every lower color must appear among the children, since the parent has a higher color. Counting down, each new color adds one distinct child per node already counted: one of color `k−1`, two of color `k−2`, four of color `k−3`, and so on. The count doubles for each of the `k−1` lower colors, so a node of color `k` requires at least `2^(k−1)` nodes in the tree, counting itself.</p><p>Thus `k ≤ floor(log₂ n) + 1`. For `n ≤ 100,000`, 17 colors suffice, so the solution's limit of 20 is safe.</p></details> | `O(nk²)` |
| 2873 | [Roller Coaster](2873_rollercoaster.cc) | Construct a zigzag path based on grid parity | `O(rc)` |
| 2887 | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm | `O(n log n)` |
| 3015 | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights | `O(n)` |
| 3197 | [Swan Lake](3197_swan_lake.cc) | Multi-source BFS and Union-Find for incremental connectivity | `O(rc·α(rc))` |
| 5719 | [Almost Shortest Path](5719_almost_shortest_path.cc) | Run Dijkstra twice, blocking every edge on any shortest path between runs | `O(n² + m log n)` |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
