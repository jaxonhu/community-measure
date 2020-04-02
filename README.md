### Community detection measures

#### NMI(normalized mutual information)

NMI指标用来比较社区检测结果与真实结果的差异，取值区间在0~1之间，NMI值越大表示社区划分结果约接近真实结果。

使用方法： 

1. make （如编译不通过，修改makefile）
2. ./nmiMeasure ../input/real_set ../input/test_set

real_set为真实社区集合

```
#	community_id
1	1
2	1
3	1
4	1
5	2
6	2
7	2
8	2

```

test_set为测试集合

```
# 	community_id
1	1
3	1
2	1
4	1
5	2
7	2
6	3
8	3


```


#### modularity(模块度)

modularity用来比较网络中社区的划分情况，直观理解社区划分如果能让内部节点之间联系紧密，与社区外部节点稀疏，则社区划分效果越好。

使用方法：

1. make
2. ./modularity ../input/graph_file  ../input/community_file

graph_file的数据集为 https://snap.stanford.edu/data/facebook_combined.txt.gz

community_file 为社区划分结果，输出格式与上方类似；