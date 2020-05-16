# HUAWEI-Code-Craft-2020
## Datasets and codes for the HUAWEI-Code-Craft-2020
### 初赛
#### Datasets
data | result | edge | node | ansnum
-|-|-|-|-
[test_data1.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/test_data1.txt) | [result1.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/result1.txt) | 5030 | 6008 | 56
[test_data2.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/test_data2.txt) | [result2.rar](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/result2.rar) | 28W | 30000 | 1004812
[test_data3.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/test_data3.txt) | [result3.rar](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/result3.rar) | 28W | 25700 | 2896262
[test_data4.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/test_data4.txt) | [result4.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/Preliminary%20Contest/result4.txt) | 24W | 30000 | 561356
#### 优化思路
* IO优化  读入mmap  写入fwrite
* 反向构图  记录三步以内能到达起始点的点
* 多线程 实际使用4线程
* 少用STL
* 递归改迭代
#### 最终成绩
* 得分0.2622  
* 杭厦赛区第14名
### 复赛
#### Datasets
data | result | ansnum
-|-|-
[test_data.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/semi-final/test_data.txt) | [result.txt](https://github.com/wpf-990213/HUAWEI-Code-Craft-2020/blob/master/semi-final/result.txt) | 47
#### 优化思路
* 反向搜时保存路径
* 用数组模拟vector
* 分页fwrite写入
* 使用原子操作开多线程，更好地均衡任务量
#### 最终成绩
* 得分10.0759
* 杭厦赛区第6名
