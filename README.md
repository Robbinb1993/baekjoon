# Baekjoon solutions

My C++ solutions for [Baekjoon Online Judge](https://www.acmicpc.net/).
Each source file is a standalone submission named after its problem number.

| Problem | Solution | Approach |
| --- | --- | --- |
| 2887 | [Svemir](2887_svemir.cc) | Sort by each coordinate, then run Prim's algorithm |
| 3015 | [Oasis Reunion](3015_oasis_reunion.cc) | Monotonic stack with counts for equal heights |

Compile and run one solution at a time. For example:

```sh
mkdir -p build
g++ -std=c++17 -O2 2887_svemir.cc -o build/2887
./build/2887 < input.txt
```
