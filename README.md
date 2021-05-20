# zhli-data-ana-homework
# Chapter 1 ROOT TTree 初阶
## homework 1.1
**参考代码[tree.cc](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/tree.cc)和[readTree.cc](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/tree.cc)将新参数存入新的ROOT文件**
- 1 利用两端时间和能量信息求出入射粒子位置：$t_{x}$和$q_{x}$。注意：不得使用$\lamda$与$v_{sc}$
  - [homework1.1-1](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/homework1.1-1.html)：找出tu-td的中心位置和两侧边界，根据几何条件确定tx = a * (tu - td) + b 中的a, b值；
  - [homework1.1-2](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/homework1.1-2.html)：利用两端qu，qd的信号，计算入射位置$q_{x}$；
- 2 中子能量ce
  - TOF 刻度，
  - [homework1.1-3](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/homework1.1-3.html)：利用TOF中的$\gamma$峰位置，对TOF进行绝对的刻度（找到飞行时间零点）；
  - [homework1.1-4](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/homework1.1-4.html)：对TOF进行常数修正，将飞行距离归一到100 cm，生成新的TOF参数ntof；计算中子能量ce；
  - [homework1.1-sum](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/homework1.1-sum.html)：总结，在新文件中加入tx，qx，ntof，ce参数，并保留原来的所有参数；
  - [生成新root代码](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.1/readTree_xi.cc)
## homework 1.2
- 用tree-makeclass的方法，将veto信息加入到代码，并生成新的root文件，[homework1.2](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.2/homework1-2.html)
- 生成新root文件代码[treeADC_xi.h](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.2/treeADC_xi.h)和[treeADC_xi.C](https://dragon-xi.github.io/zhli-data-ana-homework/homework1.2/treeADC_xi.C)

# Chapter 2 PPAC数据处理
## homework 2.1
### example
 - [exercise2.1](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/example_li/exercise2.1.html):以PPAC数据为例，对数据粗略浏览、挑选有效事件，排除偶然符合事件；
 - [exercise2.2](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/example_li/exercise2.2.html):利用MakeClass生成的.C与.h文件，将分析代码写入其中，调用函数分析数据；
 - [exercise2.3](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/example_li/exercise2.3.html):利用MakeClass生成的.C与.h文件，用Makefile（main.cpp）编写可执行程序；
 - [exercise2.4](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/example_li/exercise2.4.html):跳出MakeClass的限制，编写新的ana.C, ana.h, main.cpp文件并继承MakeClass生成的.C与.h文件，，用Makefile编写可执行程序；
### homework
 - [分析代码](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/homework2.1_Code.html)
 - [检查残差](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/homework2.1_Chi2.html)
 - [重构靶](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/homework2.1_targetpos.html)
 - [效率计算](https://dragon-xi.github.io/zhli-data-ana-homework/homework2.1/homework2.1_efficiency.html)
