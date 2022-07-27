# HighPerformanceRoutingAlgorithmSimulator
# Introduction

用C++写的高性能路由算法模拟器，用于模拟消息的路由过程，模拟器主要实现网络的结构，消息结构，路由算法。模拟随着注入率的增加，平均延迟和吞吐量的变化曲线。



# 高性能网络模拟器代码流程图
![image](https://github.com/gittxy/HighPerformanceRoutingAlgorithmSimulator/blob/master/%E9%AB%98%E6%80%A7%E8%83%BD%E7%BD%91%E7%BB%9C%E6%A8%A1%E6%8B%9F%E5%99%A8%E4%BB%A3%E7%A0%81%E6%B5%81%E7%A8%8B%E5%9B%BE.png)


# 平面自适应无死锁路由算法流程图
![image](https://github.com/gittxy/HighPerformanceRoutingAlgorithmSimulator/blob/master/%E5%B9%B3%E9%9D%A2%E8%87%AA%E9%80%82%E5%BA%94%E6%97%A0%E6%AD%BB%E9%94%81%E8%B7%AF%E7%94%B1%E7%AE%97%E6%B3%95%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

# Network Structure

- Q2DTorusNode中定义了网络节点。

- Q2DTorus定义了整个网络结构，实现的是mesh网络结构，设置每个节点的id，每一维的坐标，以及相邻的节点，缓存等。



# Message Structure

- Message消息的定义，定义消息的长度，消息的源节点和目的节点。

- Event中的genMes()函数用于产生消息，实现了不同流量模式下产生消息的情况；forWardMes()函数实现flit如何在节点之间向前移动，大概是每个周期，如果flit是header flit会根据路由算法选择的下一跳节点，占据当前节点和下一跳节点之间的链路，占据下一跳节点的buffer。如果flit是body flit会跟着前面的flit向前移动一步。如果是tail flit，会向前移动一步并释放buffer，之后统一释放链路。代码150-172表示当header flit没有到达目的节点时，并且header flit发生阻塞的情况，其后的flit会向前移动一步，到每个flit的前一个flit所在的位置。代码173-194表示当header flit没有到达目的节点时，并且header flit没有发生阻塞的情况，所有flit都向前移动一步，包括header flit。代码198-223表示当header flit到达目的节点。



# Routing Algorithm

Routing中实现具体的路由算法，Allrouting是基类，Routing继承它，主要是重写forward()函数。由于以前实现的是torus网络的路由算法，所以会判断是否走环链路，mesh是不需要的。在forward()函数中实现自己的路由算法，根据当前节点与目的节点之间各个方向的偏移以及路由算法的条件，确定可以往哪个方向路由，再检查缓存和链路的占用情况，确定下一跳的节点。





