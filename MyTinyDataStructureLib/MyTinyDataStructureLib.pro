TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Algorithm/Kmp.cpp \
        Algorithm/Recursion.cpp \
        Algorithm/SymbolPairDetection.cpp \
        DString/DString.cpp \
        DemoTest/DemoTest.cpp \
        Exception/Exception.cpp \
        Object/Object.cpp \
        main.cpp

HEADERS += \
    Algorithm/BTreeAlgorithm.h \
    Algorithm/GraphAlgorithm.h \
    Algorithm/Kmp.h \
    Algorithm/LinkListAlgorithm.h \
    Algorithm/QueueSolution.h \
    Algorithm/Recursion.h \
    Algorithm/Sort.h \
    Algorithm/SymbolPairDetection.h \
    Array/Array.h \
    Array/DynamicArray.h \
    Array/StaticArray.h \
    DString/DString.h \
    DemoTest/DemoTest.h \
    Exception/Exception.h \
    Graph/Graph.h \
    Graph/LinkListGraph.h \
    Graph/MatrixGraph.h \
    List/CircleLinkList.h \
    List/DualCircleLinkList.h \
    List/DualLinkList.h \
    List/DualStaticLinkList.h \
    List/DynamicSeqList.h \
    List/LinkList.h \
    List/LinuxList.h \
    List/List.h \
    List/SeqList.h \
    List/StaticLinkList.h \
    List/StaticSeqList.h \
    Object/Object.h \
    Queue/LinkQueue.h \
    Queue/Queue.h \
    Queue/StackToQueue.h \
    Queue/StaticQueue.h \
    SmartPointer/Pointer.h \
    SmartPointer/SharedPointer.h \
    SmartPointer/SmartPointer.h \
    Stack/LinkStack.h \
    Stack/QueueToStack.h \
    Stack/Stack.h \
    Stack/StaticStack.h \
    Tree/BTree.h \
    Tree/BTreeNode.h \
    Tree/GTree.h \
    Tree/GTreeNode.h \
    Tree/Tree.h \
    Tree/TreedNode.h
