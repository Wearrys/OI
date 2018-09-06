% Bernoulli Number and Power Sum
% Wearry

## Description

&emsp;&emsp;Calculate: 

$$ S_k(n) = \sum_{i = 0}^{n - 1} i^k $$

## Transform

$$ 
\begin{aligned}
S_{m+1}(n) + n^{m+1} &= S_{m+1}(n + 1) \\
                     &= \sum_{k = 0}^{n - 1} (k + 1)^{m+1} \\
                     &= \sum_{k = 0}^{m + 1} {m + 1 \choose k} S_k(n)
\end{aligned}
\eqno(1.1)
$$

$$ 
\mathrm{Let} \,\, \hat{S}_k(n) = \frac{1}{k + 1} \sum_{j = 0}^{k} {k + 1 \choose j} B_j n ^ {k + 1 - j} \eqno(1.2)
$$

$$
\mathrm{Where} \,\, {B_i} \,\, \mathrm{follow:} \sum_{j = 0}^{m} {m + 1 \choose j} B_j = [m = 0] \eqno(1.3)
$$

## Proof

$$ \hat{S}_k(n) = S_k(n) $$ 

&emsp;&emsp;
Considering proof below by induction, assume that $\forall \,\, 0 \le j < m: \hat(S)_j(n) = S_j(n)$, 
now to proof $\hat{S}_m(n) = S_k(n)$.

&emsp;&emsp; 
Minus $S_{m+1}(n)$ from both left and right part of equation(1.1):

$$ 
\begin{aligned}
n^{m+1} &= \sum_{k = 0}^{m} {m + 1 \choose k} S_k(n) \\
        &= \sum_{k = 0}^{m} {m + 1 \choose k} \hat{S}_k(n) + (m+1)\Delta \\
        &= \sum_{0 \le j \le k \le m} {m + 1 \choose k} {k + 1 \choose k - j} \frac{B_{k-j} n^{j+1}}{k + 1} + (m+1)\Delta \\
        &= \sum_{k = 0}^{m} {m + 1 \choose k} \frac{1}{k+1} \sum_{j = 0}^{k} {k + 1 \choose j + 1} B_{k-j}n^{j+1} + (m+1)\Delta \\
        &= \sum_{k = 0}^{m} {m + 1 \choose k} \sum_{j = 0}^{k} {k \choose j} \frac{B_{k-j}n^{j+1}}{j+1} + (m+1)\Delta \\
        &= \sum_{j = 0}^{m} {m + 1 \choose j} \frac{1}{j+1} n^{j+1} \sum_{k = j}^{m} B_{k-j} {m + 1 - j \choose k-j} + (m+1)\Delta \\
        &= n^{m + 1} + (m+1)\Delta
\end{aligned}
$$

&emsp;&emsp;&emsp;&emsp;
&emsp;&emsp;&emsp;&emsp;
&emsp;&emsp;&emsp;&emsp;
&emsp;&emsp;&emsp;&emsp;
&emsp;&emsp;&emsp;&emsp;
$\Delta = 0, \mathrm{Q.E.D.}$

## Generating Function

$$ 
\begin{aligned} 
\mathrm{Define}&: \\
    &G(x) = \sum_{i=1}^{\infty} \frac{1}{i!} x^i, F(x) = \sum_{i=0}^{\infty} \frac{B_i}{i!} x^i 
\end{aligned}
$$

&emsp;&emsp;
Then consider the production of function F and function G:

$$ 
\begin{aligned}
(F * G) (x) &= \sum_{i=1}^{\infty} \left( \sum_{j=0}^{i-1} B_j {i \choose j} \right) x^i \\
            &= \sum_{i=1}^{\infty} [i - 1 = 0] x ^ i \\
            &= x \\
       F(x) &= \frac{x}{e ^ x - 1}
\end{aligned}
$$

