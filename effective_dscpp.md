# 《数据结构（C++语言版）（第3版）》修正和补遗

本文为本人在阅读《数据结构（C++语言版）（第3版）》过程中发现的一些*错误*或者*个人认为*可完善之处的摘要，均为个人见解。

《数据结构（C++语言版）（第3版）》是邓俊辉教授所著的清华大学计算机系列教材，是数据结构和算法领域一本不可多得的极为优秀本土著作：这本书的豆瓣评分高达9.4分，与《算法导论》、《数据结构与算法分析》、《算法（第4版）》等老牌圣经处于同一水平。

本人是在[阅读一位dalao的推荐文章](https://zhuanlan.zhihu.com/p/126386159)后开始阅读这本书的，这篇文章对该书同样给予极高评价。

在该书的[课程主页](https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/)上可以下载包含教材和配套习题解析的PDF文件。

以下是《修正和补遗》正文。本文仍在不断更新。

---

1. 第68页注释1：根据已经通过的C++ 11标准，这一语义正式确定为使用 `using` 关键字表达。即：

   ```c++
   template <typename T>
   using ListNodePosi = ListNode<T> *;
   ```

2. 全书：较多使用Modern C++来说明而非“C with Classes”，很多地方可以换用为更加先进高效的C++实现。

   如：

   1.  `typedef` 的使用可很大程度上被 `using` 替代，考虑到后者支持泛型，应尽量降低、最好是完全避免前者的出现。
   2. 不应再使用字符数组，而应使用 `string`。
   3.  使用带*作用域的枚举（`enum class`）*替代*无作用域的C式枚举*以提高封装性并降低命名空间污染。

3. 第101页代码4.9，缺少对 `nCheck` 和 `nSolu` 的定义和解释。

4. 第101页代码4.9使用 `solu.find()` 搜索，但按前文实现的“从后往前”查找无法工作。调转为STL的“从前向后”的实现才能工作。

5. 第101页代码4.9第16行，循环等价条件改为其*等价*布尔表达式 `!(q.m_x == 0 && q.m_y >= N)  // 当连第一个放置都已经越界时终止` 将明显更易于理解。

6. 全书：一些实现和名称可改为“更C++”、“更STL”的风格。如使用下划线而非小驼峰作为方法等的命名是C++业界的传统。此外一些命名可改为更贴近STL、更遵照习惯和传统的风格，如第70页代码3.2及后续实现 `insertB` 改为 `insert_before`，`insertAsFirst` 改为 `push_front`，`insertAsLast` 改为 `push_back` 会更贴近STL。除此以外，一些类型别名，如 `ListNodePosi` 改名为 `iterator` 同样会更符合习惯和传统。

7. 第103页代码4.12，这样的邻格转入方式只有在整个二维数组*都是连续分配*时才有效。这意味着通常用于创建二维数组的方式，即：

   ```c++
   const auto N = 8;
   Cell **labyrinth = new Cell *[N];
   for (int i = 0; i < N; i++)
       labyrinth[i] = new Cell[N];
   ```

   是**不能**正常转入邻格的。原因是每执行一次循环都会申请大小为 `N` 的空间，这些空间整体上并不是连续的。

   要使本代码的邻格转入正常工作，需按以下方式申请连续分配的二维数组空间：

   ```c++
   const auto N = 8;
   Cell **labyrinth = new Cell *[N];
   Cell *buffer = new Cell[N * N];
   for (int i = 0; i < N; i++)
       labyrinth[i] = buffer + i * N;
   ```

8. 第123页代码5.9，`release` 函数未定义。一种可能的实现如下（未测试）：

   ```c++
   template<typename TT>
   static inline void release(TT *&p) {
       if (std::is_array<TT>())
           delete[] p;
       else delete p;
   }
   ```

9. 第133页代码5.19，二叉树后序遍历算法的迭代版可改进为更易理解的实现：

   ```c++
   inline void cal_undermost(iterator e, std::stack<iterator> &s) {
       s.push(e);
       while (e != nullptr) {
           if (has_left(e))
               s.push(e = e->left);
           else
               s.push(e = e->right);
       }
       s.pop();
   }
   
   void traverse_postorder_iterate(iterator x, Visitor visitor) {
       std::stack<iterator> nodes;
       if (x != nullptr) cal_undermost(x, nodes);
   
       while (!nodes.empty()) {
           x = nodes.top();
           nodes.pop();
           visitor(x->data);
   
           if (is_left(x) && has_right(x->parent)) // 如果有右兄弟
               cal_undermost(x->parent->right, nodes); // 入栈右兄弟下行至最底端的路径
       }
   }
   ```
   
   相比书中的示例实现，个人认为此处给出的这一实现更易理解。`cal_undermost` 函数负责计算下行至最底端的路径（无论向哪个方向下行）并入栈。对于栈中的每一个元素（注意第一个元素是从初始节点开始最底端的元素），首先出栈并访问；再判断它是否有右兄弟，若有，列其右兄弟的下行路径并入栈。
   
10. 习题解析第126页问题6-9：题干“其余顶点到它的距离的最大值”宜改为“其余*每一个顶点到它的最小距离*中的最大者”，表述更为清晰严谨。

11. 第165页，第6.7.4节第一段，*习题[6.14]*应为*习题[6-15]*。

12. 第161页图6.7、第163-164页图6.8，若按照*字典序升序*给节点编号（起使节点为0，随后A-Z按1-26编号），则依据第156页给出的*首个邻接节点`first_nbr`*和*下一个邻接节点`next_nbr`*按从大到小搜索的顺序（似乎只有这样的顺序是正确的）搜索邻接节点，则先搜索到的会是字母靠后的节点，然而这两幅图中的实例都是首先访问字母靠前的节点。因此需要注意，要想得到和图示一致的结果，必须按照*字典序降序*给节点编号。