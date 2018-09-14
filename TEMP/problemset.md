% 清华集训模拟赛
% Wearry 
% Stay determind!

&emsp;&emsp;&emsp;
开启`-O2 -std=c++11`, 题目的栈空间限制与内存限制相同.

\newpage
# 折射

        refract.cpp/in/out
        Time Limit: 1s
        Memory Limit: 256MB

## Description

&emsp;&emsp;
小Y 十分喜爱光学相关的问题, 一天他正在研究折射.

&emsp;&emsp;
他在平面上放置了 $N$ 个折射装置, 他希望利用这些装置画出美丽的折线.
折线从某个装置射出, 并且只能在装置处转向, 假设经过的装置坐标依次为 $(X_1, Y_1), (X_2, Y_2), \dots (X_K, Y_K)$, 则必须满足:

- $\forall j \in (1, K], \,\, Y_j < Y_{j-1}$

- $\forall j \in (2, K], \,\, X_{j-2} < X_{j} < X_{j-1} \,\, \mathrm{or} \,\, X_{j-1} < X_{j} < X_{j-2}$

&emsp;&emsp;
现在他希望你能告诉他, 一共有多少种不同的光线是他能画出来的,
两种光线不同当且仅当经过点的集合不同.

## Input Format

&emsp;&emsp;
输入数据第一行包含一个正整数 $N$, 表示折射装置的数量.

&emsp;&emsp;
接下来 $N$ 行, 每行两个整数, 表示一个折射装置的坐标.

## Output Format

&emsp;&emsp;
输出一行一个整数, 表示答案对 $10^9+7$ 取模的结果.

## Sample Input

        4
        2 2
        3 1
        1 4
        4 3

## Sample Output

        14

## Constraints

&emsp;&emsp;
对于 $100\%$ 数据 $\forall i \neq j, \,\, X_i \neq X_j \,\, \mathrm{and} \,\, Y_i \neq Y_j$.

- Subtask1 (11pts): $N \le 700, 1 \le X_i, Y_i \le N$

- Subtask2 (14pts): $N \le 1000, 1 \le X_i, Y_i \le N$

- Subtask3 (21pts): $N \le 3000, |X_i|, |Y_i| \le 10^9$

- Subtask4 (54pts): $N \le 6000, |X_i|, |Y_i| \le 10^9$

\newpage
# 序列

        sequence.cpp/in/out
        Time Limit: 1s
        Memory Limit: 256MB

## Description

&emsp;&emsp;
小G 发现了一个神秘的序列, 满足

- $x_1 = 1$
- $x_{2n} = -x_n$
- $x_{2n-1} = (-1)^{n+1}x_n$

&emsp;&emsp;
经过计算, 他得到了这个数列的所有信息, 现在他希望你能回答他两种类型的询问:

- $1 \,\, N$ 求 $x_N$.

- $2 \,\, N$ 求 $\sum_{i=1}^{N} x_i$.

## Input Format

&emsp;&emsp;
第一行包含一个正整数 $Q$, 表示询问组数.

&emsp;&emsp;
接下来 $Q$ 行每行两个整数, 表示一组询问.

## Output Format

&emsp;&emsp;
对于每组询问输出一行一个整数, 表示答案.

## Sample Input

        2
        1 1
        2 2

## Sample Output

        1
        0

## Constraints

&emsp;&emsp;
对于 $100\%$ 的数据, $Q \le 2 \times 10^5$.

- Subtask1 (12pts): $N \le 10^7$

- Subtask2 (7pts): 仅包含第一种询问.

- Subtask3 (33pts): $N \le 10^{18}$

- Subtask4 (48pts): $N \le 2^{61}$

\newpage
# 求和

        calc.cpp/in/out
        Time Limit: 1s 
        Memory Limit: 256MB

## Description

&emsp;&emsp;
给定$N$, 求:

$$\sum_{a=1}^{N}\sum_{b=a+1}^{N} [a+b \mid a \times b]$$

## Input Format

&emsp;&emsp;
输入一行一个整数, 表示 $N$.

## Output Format

&emsp;&emsp;
输出一行一个整数, 表示答案.

## Sample Input

        15

## Sample Output

        4

## Constraints

- Subtask1 (14pts): $N \le 5000$.

- Subtask2 (19pts): $N \le 10^7$.

- Subtask3 (19pts): $N \le 10^8$.

- Subtask4 (19pts): $N \le 10^9$.

- Subtask5 (29pts): $N \le 2^{31} - 1$.
