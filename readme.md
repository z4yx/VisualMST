###Visual MST 设计说明


####程序功能
Visual MST 是一个求解欧几里得最小生成树, 并可视化展示的工具. 目前支持从文件读入点集, 可视化编辑点集, 用三角剖分或朴素的Prim求解问题等功能. 使用三角剖分算法计算时还能够显示Delaunay三角剖分和Voronoi图.

####编译方法
本程序无额外依赖项目, 使用Qt标准的qmake->make流程编译即可.

####实现原理

#####GUI

程序的GUI使用Qt创建, 核心部分采用Qt的Graphics组件, 使得在大数据情况下保持较好的性能. GraphicsItem本身支持选中, 拖拽等功能, 简化了用户交互的处理逻辑. 对于需要特殊事件处理的图形对象, 继承相应的GraphicsItem, 重载xxxEvent函数获取事件.

在没有直接依赖关系的组件之间, 事件的传递均采用Qt的"信号和槽"机制, 解除组件耦合, 使得设计更加灵活.

#####算法

程序共实现两种算法, 基于Prim直接计算的MST朴素算法, 以及先三角剖分再计算MST的高效算法.

朴素的Prim算法直接把问题转换为完全图求解MST, 时间复杂度为O(n<sup>2</sup>).

高效算法在Delaunay三角剖分的基础上采用Kruscal算法求解, 三角剖分算法由[Triangle](http://www.cs.cmu.edu/~quake/triangle.html)库提供.

#####性能优化

程序设计时对于数据量较大的情况作了优化. 首先是所有算法均在独立的线程中运行, 避免阻塞UI线程. 把某些需要消耗时间较长, 且只能在UI线程进行的操作, 分解为几个部分, 插入全局的消息队列中分多次运行, 使得其他UI事件能够获得处理.

另外, Graphics组件本身也需要设定一些优化选项. 例如, 设定itemIndexMethod为NoIndex避免Bsp树索引产生的额外开销, 在点数较多时关闭抗锯齿选项等.

####感谢

本程序使用了[Triangle](http://www.cs.cmu.edu/~quake/triangle.html)提供的Delaunay三角剖分算法, 以及[GeoGebra](http://www.geogebra.org/)项目的图标库.
