% CSP2019 模拟赛
% Wearry
% Stay determined!

\begin{center}
开启 \texttt{-O2 -std=c++11}, 栈空间大小与题目空间大小一致。
\end{center}

\newpage
Game
===

        game.cpp/in/out
        Time Limit: 1s
        Memory Limit: 512MiB

Description
---

\qquad 小A和小B在玩一个游戏，他们两个人每人有 $n$ 张牌，每张牌有一个点数，
并且在接下来的 $n$ 个回合中每回合他们两人会分别打出手中的一张牌，点数**严格**更高的一方得一分，
然而现在小A通过某种神秘的方法得到了小B的出牌顺序，
现在他希望规划自己的出牌顺序使得自己在得分尽可能高的前提下出牌的字典序尽可能大。

Input Format
---

\qquad 第一行一个正整数 $n$ 表示游戏进行的轮数。

\qquad 接下来一行 $n$ 个整数，第 $i$ 个数表示第 $i$ 轮小B将要打出的牌的点数。

\qquad 接下来一行 $n$ 个整数，表示小A拥有的牌的点数。

Output Format
---

\qquad 输出一行 $n$ 个整数，表示小A出牌的顺序。

Sample Input
---

        5
        1 2 3 4 5
        3 2 2 1 4

Sample Output
---

        2 3 4 2 1 

Constraints
---

\qquad 对于 $20\%$ 的数据，$n \le 10$

\qquad 对于 $40\%$ 的数据，$n \le 3000$

\qquad 对于 $60\%$ 的数据，$n \le 6000$

\qquad 对于 $100\%$ 的数据，$n, a_i \le 100000$

\newpage
Time
===

        time.cpp/in/out
        Time Limit: 1s
        Memory Limit: 512MiB

Description
---

\qquad 小A现在有一个长度为 $n$ 的序列 $\{x_i\}$，但是小A认为这个序列不够优美。

\qquad 小A认为一个序列是优美的，当且仅当存在 $k \in [1, n]$，满足：

$$x_1 \le x_2 \le \dots \le x_k \ge x_{k+1} \ge \dots \ge x_n$$

\qquad 现在小A可以进行若干次操作，每次可以交换序列中相邻的两个项，
现在他想知道最少操作多少次之后能够使序列变为优美的。

Input Format
---

\qquad 第一行一个正整数 $n$，表示序列的长度。

\qquad 接下来一行 $n$ 个整数，表示初始的序列。

Output Format
---

\qquad 输出一行一个整数，表示最少需要的操作次数。

Sample Input
---

        5
        3 4 5 1 2

Sample Output
---

        1

Constraints
---

\qquad 对于 $30\%$ 的数据，$n \le 12$

\qquad 对于 $60\%$ 的数据，$n \le 100000, a_i$ 互不相同

\qquad 对于 $100\%$ 的数据，$n, a_i \le 100000$

\newpage
Cover
===

        cover.cpp/in/out
        Time Limit: 1.5s
        Memory Limit: 512MiB

Description
---

\qquad 小A现在想用 $m$ 条彩灯去装饰家中的走廊，
走廊可以视作一个 $[1, n]$ 的区间，
每一条彩灯都能覆盖一个子区间，并且有一个特定的美观程度。

\qquad 然而为了降低装饰的难度，
彩灯能够覆盖的区间两两之间只有包含和不相交的关系，
同时为了避免光污染，他希望每个 $[1, n]$ 中的点至多被 $k$ 条彩灯覆盖。

\qquad 现在小A希望你能告诉他，$k = 1, 2, \dots, m$ 时，
选出的彩灯的最大美观程度之和时多少。

Input Format
---

\qquad 第一行两个个整数 $n, m$ 表示区间的长度与彩灯的数量。

\qquad 接下来 $m$ 行，每行三个整数 $l_i, r_i, a_i$ 表示一条彩灯能够覆盖的区间
以及它的美观程度。

Output Format
---

\qquad 输出一行 $m$ 个整数，第 $i$ 个数表示 $k=i$ 时的最大美观程度。

Sample Input
---

        25 6
        1 2 10
        2 3 10
        1 3 21
        3 4 10
        4 5 10
        3 5 19

Sample Output
---

        41 80 80 80 80 80 

Constraints
---

\qquad 对于 $25\%$ 的数据，$m \le 20$

\qquad 对于 $45\%$ 的数据，$n, m \le 5000$

\qquad 对于另外 $25\%$ 的数据，所有 $a_i$ 相同

\qquad 对于 $100\%$ 的数据，$1 \le l_i \le r_i \le n, m \le 300000, a_i \le 10^9$
