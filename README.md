# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).

| Problem | Solution | Approach | Time complexity |
| --- | --- | --- | --- |
| [1006](https://acmicpc.net/problem/1006) | [Choragi the Invader](1006_choragi_the_invader.cc) | Bitmask DP on a 2×N grid with a first-column mask for wraparound | `O(n)` |
| [1420](https://acmicpc.net/problem/1420) | [Don't Go to School](1420_dont_go_to_school.cc) | Minimum vertex cut via vertex splitting and Ford–Fulkerson<details><summary>Why max flow counts the tiles to block</summary><p>Split each blockable tile into an entrance and an exit joined by an edge of capacity 1. For nonadjacent endpoints, max flow counts paths that share no intermediate tiles, and max-flow min-cut gives the same number of tiles needed to block every route.</p></details> | `O(rc)` |
| [1602](https://acmicpc.net/problem/1602) | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time<details><summary>Why processing holdup times in order works</summary><p>For active endpoints, consider only paths through vertices activated so far. `dist` is the shortest distance among those paths. `distWithHoldup` is the lowest total cost so far: path length plus the largest holdup on that same path.</p><p>Activate vertices in order of increasing holdup time. For each new vertex `k`, update `dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v])`. Then, for active endpoints, try the updated `dist[u][v] + holdup[k]` against the best total cost so far.</p><p>If the shortest path avoids `k` entirely, it was already available at an earlier step that added no more than `holdup[k]` to its length. A path first becomes eligible when all its vertices are active, including both endpoints. At that step, the newly activated vertex has the largest holdup on the path. Once all vertices are active, the best total cost so far is the global optimum.</p></details> | `O(n³ + m + q)` |
| [1648](https://acmicpc.net/problem/1648) | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings | `O(rc·2ᶜ)` |
| [1693](https://acmicpc.net/problem/1693) | [Tree Coloring](1693_tree_coloring.cc) | Tree DP with a logarithmic color bound<details><summary>Why extra colors help and how many to try</summary><p>Think bottom-up: three subtrees may be cheapest with root colors 1, 2, and 3. Giving their parent color 4 can cost less than forcing one of those subtrees to change its root color.</p><p>The tricky part is bounding the colors that the tree DP needs to try. In a minimum-cost coloring, a node of color `k` must have a neighbor of every lower color. If one is missing, recoloring the node with that color lowers the cost.</p><p>Root the tree at the node of color `k` and follow only lower colors. Every lower color must appear among the children, since the parent has a higher color. Counting down, each new color adds one distinct child per node already counted: one of color `k−1`, two of color `k−2`, four of color `k−3`, and so on. The count doubles for each of the `k−1` lower colors, so a node of color `k` requires at least `2^(k−1)` nodes in the tree, counting itself.</p><p>Thus `k ≤ floor(log₂ n) + 1`. For `n ≤ 100,000`, 17 colors suffice, so the solution's limit of 20 is safe.</p></details> | `O(nk²)` |
| [2336](https://acmicpc.net/problem/2336) | [Excellent Students](2336_excellent_students.cc) | Process students by X rank with a prefix-min segment tree<details><summary>Why the prefix minimum is enough</summary><p>Process students in increasing `X` rank. Every student already in the tree ranks better in `X`. For a student with ranks `(x, y, z)`, query the smallest `Z` among stored students with `Y` in `[1, y−1]`. If that minimum is below `z`, someone ranks better in all three exams. Otherwise the student is excellent: everyone still to come ranks worse in `X`. Then store `z` at index `y`.</p></details> | `O(n log n)` |
| [2873](https://acmicpc.net/problem/2873) | [Roller Coaster](2873_rollercoaster.cc) | Construct a zigzag path based on grid parity | `O(rc)` |
| [2887](https://acmicpc.net/problem/2887) | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm | `O(n log n)` |
| [3015](https://acmicpc.net/problem/3015) | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights | `O(n)` |
| [3197](https://acmicpc.net/problem/3197) | [Swan Lake](3197_swan_lake.cc) | Multi-source BFS and Union-Find for incremental connectivity | `O(rc·α(rc))` |
| [5719](https://acmicpc.net/problem/5719) | [Almost Shortest Path](5719_almost_shortest_path.cc) | Run Dijkstra twice, blocking every edge on any shortest path between runs | `O(n² + m log n)` |
| [8462](https://acmicpc.net/problem/8462) | [Power of an Array](8462_to_power_of_an_array.cc) | Mo's algorithm with frequency updates | `O(q log q + (n + q)√n)` |
| [9373](https://acmicpc.net/problem/9373) | [Getting Through](9373_getting_through.cc) | Binary search the radius, checking whether obstacles connect both walls | `O((n + 1)² log(w/ε))` |
| [13263](https://acmicpc.net/problem/13263) | [Sawing Trees](13263_sawing_trees.cc) | DP optimized with a monotone convex hull trick | `O(n)` |
| [13308](https://acmicpc.net/problem/13308) | [Gas Stations](13308_gas_stations.cc) | Dijkstra over (city, cheapest fuel price so far), with price limit P | `O(nP + mP log(mP))` |
| [13511](https://acmicpc.net/problem/13511) | [Tree and Queries 2](13511_tree_and_queries_2.cc) | Binary lifting for path distances and k-th vertices | `O((n + q) log n)` |
| [16993](https://acmicpc.net/problem/16993) | [Maximum Subarray Sum Queries](16993_maximum_subarray_sum_queries.cc) | Segment tree storing sum, best prefix, suffix, and subarray | `O(n + q log n)` |
| [17071](https://acmicpc.net/problem/17071) | [Hide and Seek 5](17071_hide_and_seek_5.cc) | Simulate reachable positions up to L with 64-bit bitsets | `O(L√L)` |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
