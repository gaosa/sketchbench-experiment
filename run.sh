g++ -std=c++11 -O3 task/topk.cpp
./a.out a 512 > result/topk/a.txt 2>&1 &
./a.out c 512 > result/topk/c.txt 2>&1 &
./a.out cu 512 > result/topk/cu.txt 2>&1 &
./a.out cm 512 > result/topk/cm.txt 2>&1 &
./a.out cmm 512 > result/topk/cmm.txt 2>&1 &
./a.out cmm2 512 > result/topk/cmm2.txt 2>&1 &
./a.out csm 512 > result/topk/csm.txt 2>&1 &
./a.out lcu 512 > result/topk/lcu.txt 2>&1 &
./a.out sbf 512 > result/topk/sbf.txt 2>&1 &