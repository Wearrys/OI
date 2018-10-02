% Some Tricks in OI
% Wearry

\newpage

## 组合计数相关

### 计数技巧
  - $$x ^ {\underline{n}} = nx^{\underline{n-1}}  + (x-1)^{\underline{n}}$$

  - 对于无标号对象的计数，如果能够快速和有标号的情形相互转化，转化成对有标号对象计数可能更加简便。

  - 求满足某个条件的对象的数量的$k$次方的和的问题，可以转化成每$i$个对象同时合法会产生${k \brace i} i!$的贡献。

### 实现细节

  - 使用分治FFT求函数值时，如果递推式里有这个函数的幂的形式，要考虑每一项的计算次数来确定系数。

### 容斥应用

  - $\mathrm{Stirling}$公式可以从等价类的角度考虑并化成容斥形式，例：

    > 计算$n \times m$大小的矩阵，每一个元素的取值在$[1, C]$之间，且任意两行两列不等价的方案数。

    首先通过下降幂保证任意两行不等价，令：

    $f(i)$表示所有列等价类个数小于等于$i$的方案 

    $g(i)$表示所有列等价类个数恰好等于$i$的方案

    $$ \begin{aligned}
        f(x) &= (C^x)^{\underline{n}} \\ 
             &= \sum_{i=1}^{x} {x \brace i} g(i) \\
    \end{aligned} $$

    可以$\mathrm{Stirling}$反演：

    $$ \begin{aligned}
        g(x) &= \sum_{i=1}^{x} (-1)^{x-i} \begin{bmatrix} x \\ i \end{bmatrix} f(i)
    \end{aligned} $$

## 图论

### 模型构建
  - 最小割中出现负权边时，可以考虑先手动做一次增广，选择割掉一定最优的负权边，然后利用最小割在残图中调整。

## 数论相关

### 拓展$\mathrm{Euler}$定理：

  $$ a^x \equiv a^{\mathrm{min}(x, x\, \mathrm{mod} \, \varphi(p) + \varphi(p))} \,(\mathrm{mod}\,\,\mathrm{p}) $$

  本质：

  $$ a^{\varphi(p)} \equiv a^{2\varphi(p)} \,(\mathrm{mod}\,\,\mathrm{p}) $$

  证明：

  设$p = \mathrm{m1}\mathrm{m2}$，其中$\mathrm{m1}$中包含所有$a$，$p$的公共质因子。

  显然有$\mathrm{gcd}(\mathrm{m1}, \mathrm{m2}) = \mathrm{gcd}(a, \mathrm{m2}) = 1$，
  则$a^{\varphi(\mathrm{m1}\mathrm{m2})} \equiv 1 \,(\mathrm{mod}\,\,\mathrm{m2})$。

  考虑$a^{\varphi(\mathrm{m1}\mathrm{m2})} \,\mathrm{mod} \,\, \mathrm{m1}$：
  对于任意质因子$p \, | \, \mathrm{m1}$，设其在$\mathrm{m1}$中的指数为$exp$，
  在左式中其指数最小为$(p-1) \times p^{exp-1}$显然大于$exp$，所以有：

  $$ 
    \begin{aligned}
        a^{\varphi(p)} \equiv a^{2\varphi(p)} \equiv 0 \,(\mathrm{mod}\,\,\mathrm{m1}) \\
        a^{\varphi(p)} \equiv a^{2\varphi(p)} \equiv 1 \,(\mathrm{mod}\,\,\mathrm{m2}) 
    \end{aligned}
  $$

  由$\mathrm{CRT}$，$a^{\varphi(p)} \equiv a^{2\varphi(p)} \,(\mathrm{mod}\,\,\mathrm{p})$。

### 实现（卡常）技巧

  - 需要多次计算的分块结构，可以用数组存下分块的位置反复使用。

  - 杜教筛等算法中访问的形如$\lfloor \frac{n}{i} \rfloor$ 的函数值在下标较大的时候可以利用$n$ 除以这个数的唯一性存在商中。
