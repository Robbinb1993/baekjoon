# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).

| Problem | Solution | Approach |
| --- | --- | --- |
| 1006 | [Choragi the Invader](1006_choragi_the_invader.cc) | Bitmask DP on a 2×N grid with a first-column mask for wraparound |
| 1602 | [Fugitive Monkey](1602_fugitive_monkey.cc) | Floyd–Warshall in order of increasing holdup time |
| 1648 | [Grid Fill](1648_grid_fill.cc) | Bitmask DP for domino tilings |
| 1693 | [Tree Coloring](1693_tree_coloring.cc) | Tree DP with a logarithmic color bound<details><summary>Why extra colors help and how many to try</summary><p>In the sample, the edge `1–5` joins two sides of the tree. Node 1 has leaves 2, 3, and 4. Node 5 has leaves 6, 7, and 8.</p><p><strong>Sample input</strong></p><pre>8&#10;1 2&#10;3 1&#10;1 4&#10;5 6&#10;1 5&#10;5 7&#10;5 8</pre><p>With two colors, one of nodes 1 and 5 and the three leaves on the opposite side must use color 2, for a total cost of 12. Give nodes 1 and 5 colors 2 and 3, and all six leaves can use color 1. The total drops to 11, the sample output.</p><p>The tricky part is bounding the colors that the tree DP needs to try. In a minimum-cost coloring, a node of color `k` must have a neighbor of every lower color. If one is missing, recoloring the node with that color lowers the cost.</p><p>Root the tree at a node of color `k`. Follow one neighbor of each lower color, then repeat from each of those nodes. Along these branches the parent always has a higher color, so each required lower color comes from a child. Because this is a tree, the branches cannot reuse a node.</p><p>Count the nodes by color. There is one node of color `k−1`, two of color `k−2` (one for each node of a higher color), four of color `k−3`, and so on. Each lower color needs one child for every node counted so far, doubling the total. After reaching color 1, there are at least `2^(k−1)` nodes.</p><p>Thus `k ≤ floor(log₂ n) + 1`. For `n ≤ 100,000`, 17 colors suffice, so the solution's limit of 20 is safe.</p></details> |
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
