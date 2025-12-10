# 图形算法

---

### 插值算法（Interpolation）
#### 线性插值（Linear Interpolation）
* **定义**：已知的两个点之间，通过线性函数的计算方法，得到中间点的过程。
* **公式**：
  * $D(t) = D_0 + t(D_1 - D_0)$
  * 其中，$D(t)$ 是插值点，$D_0$ 和 $D_1$ 是已知的两个点，$t$ 是参数，取值范围为 $[0, 1]$。
  
  <img src="Screenshot/线性插值.png" alt="线性插值" width="600px" height="auto">
* **应用**：
  * 颜色插值
  * 纹理坐标插值
  * 顶点属性插值

#### 三角形颜色插值算法
* **定义**：通过三角形重心坐标的计算方法，得到三角形内部任意点的颜色值的过程。
* **公式**：
  * $\alpha = \frac{S_{BPC}}{S_{ABC}}$
  * $\beta = \frac{S_{APC}}{S_{ABC}}$
  * $\gamma = \frac{S_{APB}}{S_{ABC}}$
  * $\text{Color}_P = \alpha \cdot \text{Color}_A + \beta \cdot \text{Color}_B + \gamma \cdot \text{Color}_C$

  <img src="Screenshot/彩色三角形插值算法.jpg" alt="彩色三角形插值算法" width="600px" height="auto">
