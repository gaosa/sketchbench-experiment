# sketchbench-experiment

在`task/freq.cpp`中的`main`函数中：

```cpp
init_run_save<A<Hash> >(
    "/Users/GSA/Desktop/local/sketchbench-DatasetAnalyzer/dataset/webdocs00.dat",
    "webdocs",
    4, 65536, 16
);
```

这一行就是跑一次实验。实验结果的存放路径为`result/<task 种类>/<数据集名称>/<Sketch名称>/k_l_w.txt`，如`/result/freq/webdocs/a/4_65536_16.txt`。
注意在跑实验前要先将`results`中的各级目录建好，否则结果存放不进去。

## to-do

* 添加`task/topk.cpp`  --> zcxy
* 添加`task/heavychange.cpp`  --> zcxy
* 实验结果分析  --> gsa

## 运行

```
./a.out <name> <path> <res_file_name>
```