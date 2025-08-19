---
title: Cumulative Sum 2D
documentation_of: //dp/cumulative-sum-2d.hpp
---
For Cumulative Sum in 2 dimension. It cannot support modify. There are three main function.
- `add(x, y, z)`: Add z in (x, y)
- `build()`: Build the cumulative sum. After finish `add`, it can be called.
- `query(sx, sy, gx, gy)`: Get the result in [sx, sy] ~ [gx, gy].