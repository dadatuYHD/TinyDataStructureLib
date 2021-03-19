# TinyDataStructureLib

* 通过C++实现的**轻量级数据**结构库，帮助初学者**快速实践数据结构理论**，增强C++编程能力

### 类继承关系图
![text](https://github.com/dadatuYHD/TinyDataStructureLib/blob/master/Picture/Object.png?raw=true)

## 类说明

* Object：整个项目的公共抽象父类，用以重载new、new []和delete、delete[]关键字并禁止其抛出异常，规范返回结果，以统一动态内存申请的行为。**纯虚析构函数需要提供函数体，因为析构函数无法在子类中重载**
* Exception：抽象类，继承自Object父类，其包含计算、空指针、越界、内存不足和参数异常等五个子类。所有异常相关调试信息均在Exception类中实现，通过手动调用子类的构造函数进而打印异常信息：文件、行、具体错误原因
* Algorithm：包含常见的数据结构算法模块，二叉树、图、kmp、链表、八皇后、递归、排序、符号成对检测等算法类
* Pointer：继承自Object父类，对指针操做符进行重载
  1. SmartPointer：自动释放内存空间，一片内存空间只允许一个指针指向
  2. SharedPointer：标记内存空间被指针指向的数量，自动释放内存空间
* Array：抽象类，继承自Object类，定义指向数组空间的指针，实现了数组操做符的重载、数组访问等功能函数
  1. StaticAarray：通过原始数组初始化StaticAarray内存空间，并实现数组长度获取函数
  2. DynamicArray：在堆中分配DynamicArray类的内存空间
* DString：结合C语言中的字符串函数实现功能，并且保证DString对象与char *字符串的互操作，操作符重载考虑是否支持const版本
* List：线性表的公共抽象父类，实现了线性表公共的接口：增删改查、获取长度、清空线性表，包含SeqList、LinkList、 DualLinkList 三个抽象子类
  1. SeqList：实现了List中的接口，定义了**顺序表长度变量**和**指向存储空间的指针**，并定义了接口capacity()返回顺序表的容量，并且重载数组操作符，提供以数组的方式访问顺序表
      * StaticSeqList：通过数组实现存储空间分配，初始化长度为0
      * DynamicSeqList：通过构造函数初始化顺序表的容量大小，通过malloc分配存储空间，并可以在后续重新修改容量大小。**注意函数异常安全，抛出异常也不会对资源造成泄露和浪费。**
  2.  LinkList：实现了List中的接口，定义链表节点、头节点的类型，封装了访问链表节点的线性时间度操做函数，初始化头节点，链表长度
      * StaticLinkList：在单链表内部分配一片预留空间，所有节点均在这片空间进行创建和销毁。 重写内存分配和销毁函数，用于在预留空间进行操做
      * CircleLinkList：将单链表收尾连接，重写增删改查
      * LinkListAlgorithm：实现单链表的转置、两个单链表的合并、反转打印单链表
  3. DualLinkList：实现了List中的接口，定义链表节点、头节点的类型，封装了访问链表节点的线性时间度操做函数
      * DualStaticLinkList： 和静态单链表差不多的操做
      * DualCircleLinkList ：通过结合**linux内核链表**的定义方式，重新定义节点，然后重写增删改查，并结合linux内核链表重新封装了双向循环链表的访问操做
* Stack：抽象类，继承自Object父类，定义了入栈、出栈、获取栈顶元素、清除栈、获取栈长度等接口
  1. StaticStack：通过原始数组分配栈的内存空间
  2. LinkStack：通过LinkList单链表分配栈的内存空间
  3. QueueToStack：通过LinkQueue实现栈
* Queue：抽象类，继承自Object父类，定义了入队、出队、获取出队元素、清除队列、获取队列长度等接口
  1. StaticQueue：通过原始数组分配队列的内存空间
  2. LinkQueue：通过Linux内核链表分配队列的内存空间
  3. StackToQueue：通过LinkStack实现队列
* tree：抽象类，继承自Object父类，定义了指向根节点TreeNode的指针，并重载赋值操作符，定义插入、删除、查询和返回根节点、获取树的度、获取节点数量、获取树高度等接口
  1. GTree：实现tree中的接口
  2. BTree：实现tree中的接口
* TreeNode：抽象类，继承自Object父类，对new进行了重载，定义获取树节点存储区域的函数
  1. GTreeNode：通用树节点，每个树节点可以多个子节点，结合LinkList单链表，用来存储子节点地址，通过工厂模式在堆空间中创建树节点
  2. BTreeNode：二叉树，只有两个子节点，通过定义左右节点指针实现，用工厂模式在堆空间中创建树节点
* Graph：抽象类，继承自Object父类，定义接口函数：获取和设置顶点值、获取和设置边上权值，删除边、计算顶点数量、顶点出度和入度，实现深度和广度优先以及prim、kruskal、djikstra和floyd等图搜算法
  1. LinkListGraph：定义顶点结构体，结合LinkList单链表实现图，最后实现Graph类中的接口函数
  2. MatrixGraph：通过邻接矩阵的思想实现图，底层通过数组实现，最后实现Graph类中的接口函数
* DemoTest：用来测试的例程

### 例程使用方法

* 直接在main.cpp里面调用DemoTest.cpp内的函数即可





