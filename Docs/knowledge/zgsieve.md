% 洲阁筛学习
% Wearry

## Description

&emsp;&emsp;
Calculate:

$$ \sum_{i=1}^{n} F(i) $$ 

&emsp;&emsp;
where $F(x)$ is a multiplicative function.

## Divide 

&emsp;&emsp;
Firstly, we can divide the numbers to 2 parts through whether it has a prime factor that > $\sqrt{n}$.

&emsp;&emsp;
Then, the answer can be expressed as follow:

$$\sum_{i = 1}^{n} F(i) = \sum_{\substack{1 \le i \le n \\ i \text{ have no prime factors } > \sqrt{n} }} F(i) \left( 1 + \sum_{\substack{\sqrt{n} < j \le \lfloor \frac{n}{i} \rfloor \\ j \text{ is prime}}} F(j) \right)$$

### Part. 1
&emsp;&emsp;
Calculate:

$$\sum_{i = 1}^{n} F(i) = \sum_{\substack{\sqrt{n} \le i \le n \\ i \text{ is prime}}} F(i)$$

&emsp;&emsp; 
For each different value of $\lfloor \frac{n}{i} \rfloor$, and it's obviously that the number of different values is $O(\sqrt{n})$.

&emsp;&emsp;
Define $g_k(i, j)$ express sum of k-power of numbers which are conprime with the first i prime numbers and in range $[1, j]$.

&emsp;&emsp;
It's also obviously that:

$$ g_k(i, j) = g_k(i-1, j) - p_i^k g_k(i-1, \lfloor \frac{j}{p_i} \rfloor) $$

&emsp;&emsp;
We can use some tricks optimize it, such as don't calculate it when $p_i^2 > j$, because at that time:

$$ g_k(i, j) = g_k(i-1, j) - p_i^k $$

&emsp;&emsp; 
So we can get the $g_k(i, j)$ from $g_k(i-x, j)$ rapidly.

### Part. 2

&emsp;&emsp;
Calculate:

$$\sum_{i = 1}^{n} F(i) = \sum_{\substack{1 \le i \le n \\ i \text{ have no prime factors } > \sqrt{n} }} F(i)$$

&emsp;&emsp;
Similar to the Part. 1, we define $f(i, j)$ express the sum of $F(x)$ where $x \in [1, j]$ and $x$ contain a prime factor 
which in the last i prime factors less than $\sqrt{n}$.

&emsp;&emsp;
Also we get:

$$ f(i, j) = f(i-1, j) + \sum_{c = 1} F(p_i^c) f(i-1, \lfloor \frac{j}{p_i^c} \rfloor) $$ 

&emsp;&emsp;
Use the same way, we can optimize it easily.

&emsp;&emsp;
When $p_i^2 > j$:

$$ f(i, j) = f(i-1, j) + F(p_i) $$

# Usage

&emsp;&emsp;
Most of time, it can be used when we can divide the numbers we need in below 2 parts, 
and it works in $O(\frac{n^{\frac{3}{4}}}{log(n)})$ time.

