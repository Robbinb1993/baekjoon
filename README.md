# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).

| Problem | Solution | Approach | Time complexity |
| --- | --- | --- | --- |
| [1006](https://acmicpc.net/problem/1006) | [Choragi the Invader](1006_choragi_the_invader.cc) | Bitmask DP on a 2×N grid with a first-column mask for wraparound | `O(n)` |
| [1602](https://acmicpc.net/problem/1602) | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time<details><summary>Why processing holdup times in order works</summary><p>Keep two values for each pair: `dist` is the shortest distance, and `distWithHoldup` is the minimum of `path distance + maximum holdup on that path`.</p><p>Activate vertices in order of increasing holdup time. When vertex `k` is activated, run its Floyd–Warshall step to allow it as an intermediate vertex. For active endpoints `u` and `v`, try `dist[u][v] + holdup[k]` against the best total cost so far.</p><p>The shortest path at this step need not use `k`: `holdup[k]` is a cap on the holdup of every active vertex. Every path becomes eligible when its last vertex is activated, at which point the cap equals that path’s largest holdup. Taking the minimum over all steps therefore gives the optimal total cost.</p></details> | `O(n³ + m + q)` |
| [1648](https://acmicpc.net/problem/1648) | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings | `O(rc·2ᶜ)` |
| [1693](https://acmicpc.net/problem/1693) | [Tree Coloring](1693_tree_coloring.cc) | Tree DP with a logarithmic color bound<details><summary>Why extra colors help and how many to try</summary><p>Think bottom-up: three subtrees may be cheapest with root colors 1, 2, and 3. Giving their parent color 4 can cost less than forcing one of those subtrees to change its root color.</p><p>The tricky part is bounding the colors that the tree DP needs to try. In a minimum-cost coloring, a node of color `k` must have a neighbor of every lower color. If one is missing, recoloring the node with that color lowers the cost.</p><p>Root the tree at the node of color `k` and follow only lower colors. Every lower color must appear among the children, since the parent has a higher color. Counting down, each new color adds one distinct child per node already counted: one of color `k−1`, two of color `k−2`, four of color `k−3`, and so on. The count doubles for each of the `k−1` lower colors, so a node of color `k` requires at least `2^(k−1)` nodes in the tree, counting itself.</p><p>Thus `k ≤ floor(log₂ n) + 1`. For `n ≤ 100,000`, 17 colors suffice, so the solution's limit of 20 is safe.</p></details> | `O(nk²)` |
| [2873](https://acmicpc.net/problem/2873) | [Roller Coaster](2873_rollercoaster.cc) | Construct a zigzag path based on grid parity | `O(rc)` |
| [2887](https://acmicpc.net/problem/2887) | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm | `O(n log n)` |
| [3015](https://acmicpc.net/problem/3015) | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights | `O(n)` |
| [3197](https://acmicpc.net/problem/3197) | [Swan Lake](3197_swan_lake.cc) | Multi-source BFS and Union-Find for incremental connectivity | `O(rc·α(rc))` |
| [5719](https://acmicpc.net/problem/5719) | [Almost Shortest Path](5719_almost_shortest_path.cc) | Run Dijkstra twice, blocking every edge on any shortest path between runs | `O(n² + m log n)` |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
