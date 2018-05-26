g++ -std=c++11 -O3 task/topk.cpp
./a.out a 4096 > result/topk/a.txt 2>&1 &
./a.out c 4096 > result/topk/c.txt 2>&1 &
./a.out cu 4096 > result/topk/cu.txt 2>&1 &
./a.out cm 4096 > result/topk/cm.txt 2>&1 &
./a.out cmm 4096 > result/topk/cmm.txt 2>&1 &
./a.out cmm2 4096 > result/topk/cmm2.txt 2>&1 &
./a.out csm 4096 > result/topk/csm.txt 2>&1 &
./a.out lcu 4096 > result/topk/lcu.txt 2>&1 &
./a.out sbf 4096 > result/topk/sbf.txt 2>&1 &
./a.out ss 4096 > result/topk/ss.txt 2>&1 &