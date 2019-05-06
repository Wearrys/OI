% NOIP 模拟赛

\newpage
# Wheatland

      wheatland.cpp/in/out
      Time Limit: 1s
      Memory Limit: 128MB

## Description

\qquad 有一片 $n \times m$ 的麦田，
麦田上第 $i$ 行第 $j$ 列的位置可以用点对 $(i, j)$ 表示。

\qquad 每个点上有两种可能的状态，有麦子或者无麦子，
小 C 从麦田的左上角 $(1, 1)$ 出发，计划到达 $(n, m)$，
当他第一次经过一个有麦子的位置时，这个位置上的麦子会被毁坏，
现在他计划在毁坏不超过 $k$ 个位置的麦子的情况下，找到最短的路径，求最短路径的长度。

## Input Format

\qquad 第一行三个正整数 $n, m, k$

\qquad 接下来 $n$ 行，每行一个长度为 $m$ 的 $01$ 串，描述麦田的信息，'0' 表示没有麦子，'1' 表示有麦子。

## Output Format

\qquad 输出一行一个整数，表示最短路径的长度；如果不存在这样的路径，则输出 "no solution" (不包含引号)。

## Sample Input

      3 4 3
      1100
      1000
      1100

## Sample Output

      5

## Constriaints

\qquad 对于 $30\%$ 的数据，$n, m \le 4$

\qquad 对于 $70\%$ 的数据，$n, m \le 50$

\qquad 对于 $100\%$ 的数据，$n, m \le 200$

\newpage
# Calc

      calc.cpp/in/out
      Time Limit: 1s
      Memory Limit: 128MB

## Description

\qquad 小 P 对整数的约数十分感兴趣，一天他想到了一个这样的问题：

- 对于正整数 $n$ ，定义 $n$ 的特征值为其分解质因数后质因子的种类数
- 记 $f(n)$ 表示 $n$ 的所有约数的特征值的和，求 $\sum_{i=l}^{r} f(i) \bmod p$

\qquad 特别地，$1$ 的特征值为 $0$。

## Input Format

\qquad 一行三个正整数，$l, r, p$

## Output Format

\qquad 输出一行一个整数，表示答案。

## Sample Input

      10 99 120

## Sample Output

      29

## Constraints

\qquad 对于 $15\%$ 的数据，$l = r$

\qquad 对于另外 $25\%$ 的数据, $l \le r \le 10^5$

\qquad 对于另外 $35\%$ 的数据，$l = 1$

\qquad 对于 $100\%$ 的数据，$l \le r \le 10^7, p \le 10^9$

\newpage
# Game

      game.cpp/in/out
      Time Limit: 1s
      Memory Limit: 128MB

## Description

\qquad 小 A 手里有黑白两种颜色的棋子，其中黑色的棋子有 $b$ 个，白色的棋子有 $w$ 个。

\qquad 小 A 会不断进行如下的取棋子操作直到所有的棋子都被取完：

1. 如果两种颜色的棋子都存在，则随机从某种颜色的棋子中任意取走一个。
2. 否则从仅剩的棋子中任意取走一个。

\qquad 现在小 A 想知道，对于 $i \in [1, w + b]$，他在第 $i$ 次取棋子时恰好取走的是黑色棋子的概率对 $10^9 + 7$ 取模的结果是多少。

## Input Format

\qquad 一行两个正整数 $w, b$ 。

## Output Format

\qquad 输出 $w+b$ 行，第 $i$ 行表示第 $i$ 次去的棋子恰好是黑色的概率对 $10^9 + 7$ 取模的结果。

## Sample Input

      2 1

## Sample Output

      500000004
      750000006
      750000006

## Constraints

\qquad 对于 $15\%$ 的数据，$w, b \le 10$

\qquad 对于 $50\%$ 的数据，$w, b \le 1000$

\qquad 对于另外 $15\%$ 的数据，$w = b$

\qquad 对于 $100\%$ 的数据，$w, b \le 10^5$
