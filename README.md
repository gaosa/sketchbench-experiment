# sketchbench-experiment

在`task/freq.cpp`中的 main 函数中：

```
init_run_save<A<Hash> >(
    "/Users/GSA/Desktop/local/sketchbench-DatasetAnalyzer/dataset/webdocs00.dat",
    "webdocs",
    4, 65536, 16
);
```

这一行就是跑一次实验。实验结果的存放路径为`result/<task 种类>/<数据集名称>/<Sketch名称>/k_l_w.txt`，如`/result/freq/webdocs/a/4_65536_16.txt`。
注意在跑实验前要先将`results`中的各级目录建好，否则结果存放不进去。