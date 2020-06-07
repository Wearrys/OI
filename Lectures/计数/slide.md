% 计数技巧选讲
% Wearry
% Stay determined!

容斥原理
===

HAOI2018 Paint
---


---

\frametitle{\insertsubsection}

有一块长度为 $n$ 的画布，
每个位置可以染成 $[1, m]$ 这些颜色中的一种。

如果画布上恰好有 $k$ 种颜色恰好出现了 $s$ 次，
则会产生 $w_k$ 的愉悦度，求所有不同画布的愉悦度之和，
对 $998244353$ 取模。

\vspace{2ex}

$n \le 10^7, m \le 10^5, s \le 150$

---

\frametitle{\insertsubsection}

考虑先计算至少有 $i$ 种颜色出现了 $s$ 次的方案数 $g_i$：

$$
g_i = {m \choose i} {n \choose is} \frac{(is)!(m-i)^{n-is}}{(s!)^i}
$$

接下来考虑计算恰好有 $i$ 种颜色出现 $s$ 次的方案数 $f_i$：

$$
\begin{aligned}
g_i &= \sum_{j=i}^{n} {j \choose i} f_j \\
i! g_i &= \sum_{j=i}^{n} \frac{1}{(j-i)!} \times j! f_j
\end{aligned}
$$

转化成了可以卷积的形式。

Permutation
---

---

\frametitle{\insertsubsection}

对于长度为 $n$ 的排列 $\{a_i\}$ 定义其特征值为：

$$\sum_{i=1}^{n-1} a_i < a_{i+1}$$

求长度为 $n$ 的排列中特征值为 $0, 1, \dots, n-1$
的排列分别有多少个。

答案对 $998244353$ 取模。

\vspace{2ex}

$n \le 10^5$

---

直接用 `DP` 计算复杂度难以优于 $n^2$ 。

注意到特征值为 $k$ 的序列，
可以分为 $k$ 段，每一段内部是无序的。

记 $f_i$ 表示特征值为 $i$ 的序列数，则有：

$$
m!{n \brace m} = \sum_{i=1}^{m-1} f_i {n-i-1 \choose m-i-1}
$$

继续化简得到：

$$
(n-m)! m! {n \brace m} = \sum_{i=1}^{m-1} f_i (n-i-1)! \times \frac{1}{(m-i-1)!}
$$

这样得到了一个卷积形式的容斥式子， `FFT` 优化卷积计算即可。

BZOJ 2655 Calc
---

---

\frametitle{\insertsubsection}

定义序列 $\{a_i\}$ 是合法的当且仅当：

- $\forall i ,\, a_i \in [1, C]$
- $\forall i,j ,\, a_i \neq a_j$

定义序列的权值为所有元素的乘积，
求所有长度为 $n$ 的不同的合法序列的权值和，
对 $10^9 + 7$ 取模。

\vspace{2ex}

$n \le 500, C \le 10^9$

---

\frametitle{\insertsubsection}

构成相同的序列权值相等，
因此只需计算上升序列的答案的 $n!$ 倍即可。

记 $f_n$ 表示长度为 $n$ 的严格上升序列的权值和，
$f_{n, x}$ 表示长度为 $n$ 的包含元素 $x$ 的上升序列的权值和，有：

$$
f_n = \frac{1}{n} \sum_{i=1}^{C} f_{n, i} 
$$

\pause

考虑 $f_{n-i}$ 是否包含 $x$，不难得到：

$$
x^i f_{n-i} = x^i f_{n-i, x} + x^{i-1} f_{n-i+1, x}
$$

---

考虑用容斥求出 $f_{n, x}$：

$$
f_{n, x} = \sum_{i=1}^{n-1} (-1)^{i+1} x^i f_{n-i}
$$

因此：

$$
f_n = \frac{1}{n} \left(\sum_{i=1}^{n-1} g_i f_{n-i}\right)
$$

其中：

$$
g_n = (-1)^{n+1} \sum_{i=1}^{C} i^n
$$

Color
---

---

\frametitle{\insertsubsection}

有 $n$ 种不同颜色的石子，
第 $i$ 种颜色的石子有 $a_i$ 个，
你要将它们排成一个序列，
序列的权值定义为首尾相连后极大连续相同颜色段的大小乘积。

\vspace{1ex}

求所有本质不同的序列的权值和对 $998244353$ 取模的结果。

\vspace{2ex}

$n \le 10^5, \sum a_i \le 2 \times 10^5$

---

\frametitle{\insertsubsection}

首先考虑处理序列首尾不相接的情况，
令 $f_{i, j}$ 表示将 $i$ 个相同元素分成 $j$ 段的所有方案中，
每段大小的乘积和；通过组合意义不难得到：

$$f_{i, j} = {i+j-1 \choose 2j-1}$$

\pause

直接计算还是无法保证段数满足要求，不妨考虑容斥，
钦定第 $i$ 种颜色分成的段数恰好为 $b_i$ ，
则相当于要求最后没有两个相邻的段颜色相同，
因此方案数等于：

$$
\sum_{c_i \le b_i} \frac{(\sum{c_i})!}{\prod{c_i!}} \prod_{i=1}^{n} (-1)^{b_i-c_i} {b_i-1 \choose c_i-1} f_{i, b_i} 
$$

---

\frametitle{\insertsubsection}

接下来考虑首尾相连的条件：

- 不妨钦定序列开头的段是 $1$ 且结尾的段不是 $1$。
- 最后的答案除以 $1$ 的段数并乘上 $\sum{a_i}$ 即可。
- 以 $1$ 开头的方案相当于将 $c_1$ 减少 $1$。
- 以 $1$ 开头并结尾的方案相当于 $c_1$ 减少 $2$。

这样即使存在不超过 $\sum{a_i}$ 的循环节也不会有问题，
证明留作思考。

由于具有良好的形式，可以方便地使用卷积进行优化。

题目特殊性质
===

Divide
---

---

\frametitle{\insertsubsection}

对一棵 $n$ 个点的树进行如下分治操作：

1. 如果当前联通块大小不超过 $1$ ，则结束，否则执行 $2$ 。
2. 在当前联通块中任选一个点删除，
并断开与这个点相连的所有边，
对剩下的联通块递归执行 $1$ 操作。

问一共能得到多少本质不同的分治结构。

\vspace{2ex}

$n \le 5000$

---

\frametitle{\insertsubsection}

对于原树中相邻的两个点 $u, v$，
考虑断开连边分别得到一个分治结构然后合并。
不难发现 $u, v$ 各自所在的分治树中：

- 不在 $u, v$ 到根的路径上的点一定不会受到影响。
- 在到根的路径上的点对另一棵分治树不会产生影响。

\pause

于是可以令 $f_{i, j}$ 表示 $i$ 所在联通块中，
点 $i$ 在分治树上的深度为 $j$ 的方案数是多少，
合并两个相邻点所在联通块时有：

$$
f_{u, k} = \sum_{i=1}^{k} {k-1 \choose i-1} f_{u, i} \sum_{j=k-i}^{n} f_{v, j}
$$

集训队作业2018 Pigeon
---

---

\frametitle{\insertsubsection}

现在有 $n$ 个鸽笼，第 $i$ 个鸽笼有 $a_i$ 个位置，
现在共有 $\sum{a_i}-1$ 只鸽子要飞回来，
每只鸽子会在所有未满的鸽笼中随机选择一个飞入，
对于每个笼子，求其最终未满的概率。

\vspace{2ex}

$n, a_i \le 30$

---

\frametitle{\insertsubsection}

由于概率分布在不停变化，
考虑让装满的鸽笼加入可选集合中，
如果选到已经满的鸽笼，则强制重新进行一次选择，
这样概率分布与原来保持一致。

\pause
\vspace{2ex}

假设要计算 $x$ 号笼子的概率，
考虑钦定其它 $i$ 个笼子未满，
则选中一个被钦定的笼子或者 $x$ 号笼子的概率为：

$$
\sum_{x=0}^{\infty} \left(\frac{n-i-1}{n}\right)^{x} \frac{1}{n} = \frac{1}{i+1}
$$

---

\frametitle{\insertsubsection}

考虑容斥，由于钦定的位置比较好控制，
因此可以强制被钦定的位置在 $x$ 满之前都没有满，
所有这样的满足条件的序列可以用 `DP` 求出。

令 $f_{i, j}$ 表示钦定了 $i$ 个笼子，
在 $x$ 满之前一共用掉了 $j$ 个位置的序列数，则答案为：

$$
\sum_{i, j} (-1)^{i} \left(\frac{1}{i+1}\right)^j f_{i, j}
$$

其中 $(-1)^i$ 表示除了钦定的位置一定未满之外，
其它位置也可能未满的容斥系数。

JOISC 2016 Day 1 Chess
---

---

\frametitle{\insertsubsection}

有一个 $3 \times n$ 的棋盘，
棋盘上有一些位置已经放上了棋子，
现在你要将其填满棋子，
一个位置能放棋子当且仅当以下两个条件满足至少一个：

1. 这个位置的左右都有棋子。
2. 这个位置的上下都有棋子。

求有多少种不同的方案能够最终放满棋子，
两种方案不同当且仅当某一步放棋子的位置不同。

\vspace{2ex}

$n \le 2000$ 

---

\frametitle{\insertsubsection}

首先分析填棋子的条件，可以知道：

1. 对于第一行和第三行不能有两个连续的空位，否则无解。
2. 第二行的每个点有两种可能的放法。
3. 对于第二行，被棋子分割开得两个部分互不影响，可以独立求解。

\pause

考虑`DP`，记 $f_{i, j, k}$ 表示当前考虑到第二行的第 $i$ 个位置，
且它是第 $j$ 个被填上，填上的方式是 $k$，
使用组合数转移与合并即可。

Graph
---

---

\frametitle{\insertsubsection}

求所有 $2^{n \choose 2}$ 种 $n$ 个点的无向图的联通块个数的 
$k$ 次方的和。

\vspace{2ex}

$n \le 30000, k \le 50$

---

\frametitle{\insertsubsection}

考虑组合意义， $x^k$ 相当于在 $x$ 种物品种可重地选择 $k$ 次，
枚举选择的物品构成的可重集的大小：

$$
\begin{aligned}
x^k &= \sum_{i=0}^{k} {k \brace i} x^{\underline{i}} \\
&= \sum_{i=0}^{k} i! {k \brace i} {x \choose i}
\end{aligned}
$$

注意到由于 $k$ 的范围相对较小，
因此需要考虑的联通块的最大数量从 $O(n)$ 降到了 $O(k)$ ，
可以直接对于每种联通块的数量求出生成函数。

结合其它知识
===

Spanning Tree
---

---

\frametitle{\insertsubsection}

给出一个 $n$ 个点， $m$ 条边的无向图，
定义一棵生成树的权值为边权值之和的 $k$ 次方。
求图上所有不同的生成树的权值和对 $10^9 + 7$ 取模的结果。

\vspace{2ex}

$n, k \le 50, m \le \frac{n(n-1)}{2}$

---

\frametitle{\insertsubsection}

不妨将和的乘积转化成乘积的和：

$$
(w_1 + w_2 + \dots + w_{n-1})^k = 
\sum_{\sum{a_i} = k} k! \prod_{i=1}^{n-1} \frac{w_i^{a_i}}{a_i!}
$$

然后可以考虑矩阵树，将权值为 $w$ 的边设为：

$$
\sum_{i=0}^{k} \frac{w^i x^i}{i!}
$$

---

\frametitle{\insertsubsection}

这样求出的矩阵树本质上是一个多项式，
而我们希望知道的是这个多项式在 $x^k$ 项上的系数。

\pause
\vspace{2ex}

直接对未知数计算行列式是较为困难的，
我们可以使用多项式插值，
带入 $n\times k$ 个不同的 $x$ 值并计算行列式，
最后通过插值得到整个多项式即可。

清华集训 2017 Count
---

---

\frametitle{\insertsubsection}

一个 $n$ 个点的图，图中第 $i$ 个点的权值为 $a_i$ ，
对于图的任意一个生成树 $T$ ，假设第 $i$ 个点的度数为 $d_i$，
定义其权值为：

$$
\sum_{i=1}^{n} d_i^{m} \left(\prod_{i=1}^{n} a_i^{d_i} d_i^m\right)
$$

求图中所有生成树的权值和对 $998244353$ 取模的结果。

\vspace{2ex}

$n \le 3 \times 10^4, m \le 30$

---

\frametitle{\insertsubsection}

与度数相关的生成树问题，可以考虑 `Prufer` 序列：

$$
\begin{aligned}
&\sum_{\sum{d_i} = n-2} \frac{(n-2)!}{\prod{d_i!}} 
\prod_{i=1}^{n} a_i^{d_i+1} (d_i+1)^m \sum_{i=1}^{n} (d_i+1)^m \\
=& (n-2)!\prod_{i=1}^{n} a_i \sum_{\sum{d_i} = n-2} 
\prod_{i=1}^{n} \frac{a_i^{d_i} (d_i+1)^m}{d_i!} 
\sum_{i=1}^{n} (d_i+1)^m \\
=& (n-2)!\prod_{i=1}^{n} a_i \sum_{\sum{d_i} = n-2} 
\sum_{i=1}^{n} \frac{a_i^{d_i} (d_i+1)^{2m}}{d_i!} 
\prod_{j=1, j\neq i}^{n} \frac{a_j^{d_j} (d_j+1)^m}{d_j!} 
\end{aligned}
$$

---

\frametitle{\insertsubsection}

令：

$$
\begin{aligned}
A(x) = \sum_{i=0}^{\infty} \frac{x^i (i+1)^m}{i!} \\
B(x) = \sum_{i=0}^{\infty} \frac{x^i (i+1)^{2m}}{i!}
\end{aligned}
$$

则答案的生成函数 $F(x)$ 等于：

$$
\begin{aligned}
&(n-2)!\prod_{i=1}^{n} a_i  
\sum_{i=1}^{n} B(a_ix) \prod_{j=1, j\neq i}^{n} A(a_jx) \\
=&
(n-2)!\prod_{i=1}^{n} a_i  
\sum_{i=1}^{n} \frac{B(a_ix)}{A(a_ix)} 
\exp\left(\sum_{j=1}^{n} \ln(A(a_jx))\right)
\end{aligned}
$$

---

\frametitle{\insertsubsection}

忽略前面乘上的常数项，剩下的部分是：

$$
\left( \sum_{i=1}^{n} \frac{B(a_ix)}{A(a_ix)} \right)
\exp \left( \sum_{i=1}^{n} \ln(A(a_ix)) \right)
$$

要计算带 $\sum$ 的项，
先求出 $\frac{B(x)}{A(x)}$ 和 $\ln(A(x))$ ，
然后将 $x^k$ 项的系数乘以 $\sum_{i=1}^{n} a_i^k$ 即可。

2018 集训队互测 Day 5 Paint
---

---

\frametitle{\insertsubsection}

有 $n$ 个球排成一列，编号 $0$ 到 $n-1$ ，初始时均为白色，
现在你会进行两次染色，每次随机选择 $m$ 个球并将其染成黑色。

\vspace{1ex}

令 $a$ 为最小的黑球的编号，
求 $F(a)$ 的期望对 $998244353$ 取模的结果。

其中 $F(x)$ 是一个次数不超过 $m$ 的多项式，
并且其点值表示已经给出。

\vspace{2ex}

$n < 998244353, m \le 10^6$

---

\frametitle{\insertsubsection}

首先解决问题的弱化版 $F(x) = x^c$。

\vspace{2ex}

考虑期望线性性： 
$x^c$ 的期望的组合意义相当于选择 $c$ 个位置，
都比 $x$ 小的概率和，因此答案可以表示为：

$$
\sum_{i=m+1}^{m+c} {n \choose i} \sum_{j=1}^{i} G_j H_{i-j}
$$

其中 $G_n$ 表示选择的位置去重后有 $n$ 个的方案数，
$H_n$ 表示染色的位置去重后有 $n$ 个的方案数。

---

\frametitle{\insertsubsection}

不难发现：

$$
\begin{aligned}
& G_n = \sum_{i=0}^{n} (-1)^{n-i} {n \choose i} i^c \\
& H_n = {n \choose m} {m \choose 2m - n}
\end{aligned}
$$

所以对于一般的 $F(x) = \sum_{i=0}^{m} a_i x^i$：

$$
\begin{aligned}
G_n &= \sum_{i=0}^{n} (-1)^{n-i} {n \choose i} 
\sum_{j=0}^{m} a_j i^j \\
    &= \sum_{i=0}^{n} (-1)^{n-i} {n \choose i} F(i)
\end{aligned}
$$

剩下的部分都可以利用卷积优化。
