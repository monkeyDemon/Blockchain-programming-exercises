# 测试github如何插入公式
昨天上传后发现github插入latex公式存在问题。

本文件作为测试，探索如何解决

$Ch(x,y,z) = (x \land y)$

$x^2$

<a href="https://www.codecogs.com/eqnedit.php?latex=ax^{2}&space;&plus;&space;by^{2}&space;&plus;&space;c&space;=&space;0" target="_blank"><img src="https://latex.codecogs.com/gif.latex?ax^{2}&space;&plus;&space;by^{2}&space;&plus;&space;c&space;=&space;0" title="ax^{2} + by^{2} + c = 0" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=\begin{align*}&space;Ch(x,y,z)&space;&=&space;(x&space;\land&space;y)&space;\oplus&space;(\neg&space;x&space;\land&space;z)&space;\\&space;Ma(x,y,z)&space;&=&space;(x&space;\land&space;y)&space;\oplus&space;(x&space;\land&space;z)&space;\oplus&space;(y&space;\land&space;z)&space;\\&space;\Sigma_{0}(x)&space;&=&space;S^{2}(x)&space;\oplus&space;S^{13}(x)&space;\oplus&space;S^{22}(x)&space;\\&space;\Sigma_{1}(x)&space;&=&space;S^{6}(x)&space;\oplus&space;S^{11}(x)&space;\oplus&space;S^{25}(x)&space;\\&space;\sigma_{0}(x)&space;&=&space;S^{7}(x)&space;\oplus&space;S^{18}(x)&space;\oplus&space;R^{3}(x)&space;\\&space;\sigma_{1}(x)&space;&=&space;S^{17}(x)&space;\oplus&space;S^{19}(x)&space;\oplus&space;R^{10}(x)&space;\end{align*}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\begin{align*}&space;Ch(x,y,z)&space;&=&space;(x&space;\land&space;y)&space;\oplus&space;(\neg&space;x&space;\land&space;z)&space;\\&space;Ma(x,y,z)&space;&=&space;(x&space;\land&space;y)&space;\oplus&space;(x&space;\land&space;z)&space;\oplus&space;(y&space;\land&space;z)&space;\\&space;\Sigma_{0}(x)&space;&=&space;S^{2}(x)&space;\oplus&space;S^{13}(x)&space;\oplus&space;S^{22}(x)&space;\\&space;\Sigma_{1}(x)&space;&=&space;S^{6}(x)&space;\oplus&space;S^{11}(x)&space;\oplus&space;S^{25}(x)&space;\\&space;\sigma_{0}(x)&space;&=&space;S^{7}(x)&space;\oplus&space;S^{18}(x)&space;\oplus&space;R^{3}(x)&space;\\&space;\sigma_{1}(x)&space;&=&space;S^{17}(x)&space;\oplus&space;S^{19}(x)&space;\oplus&space;R^{10}(x)&space;\end{align*}" title="\begin{align*} Ch(x,y,z) &= (x \land y) \oplus (\neg x \land z) \\ Ma(x,y,z) &= (x \land y) \oplus (x \land z) \oplus (y \land z) \\ \Sigma_{0}(x) &= S^{2}(x) \oplus S^{13}(x) \oplus S^{22}(x) \\ \Sigma_{1}(x) &= S^{6}(x) \oplus S^{11}(x) \oplus S^{25}(x) \\ \sigma_{0}(x) &= S^{7}(x) \oplus S^{18}(x) \oplus R^{3}(x) \\ \sigma_{1}(x) &= S^{17}(x) \oplus S^{19}(x) \oplus R^{10}(x) \end{align*}" /></a>

 逻辑运算   | 含义           |
 ---------- | -------------- |
 $ \land  $ | 按位“与”       |
 $ \neg  $  | 按位“补”       |
 $ \oplus $ | 按位“异或”     |
 $ S^{n} $  | 右移n个bit     |
 $ R^{n} $  | 循环右移n个bit |
