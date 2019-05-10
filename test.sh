#!/bin/bash
# 作成したプログラムhoge.cpp
# サンプル入力hoge1.in
# サンプル出力hoge1.ans

read file
g++ ${file}.cpp -std=c++11 -pthread
testfiles="${file}*.in"

count=1
size=${#testfiles}
for filepath in ${testfiles}
do
    # 初回のみ
    # ./a.out < ${filepath} 1> ${file}${count}.ans
    
    ./a.out < ${filepath} 1> ${file}${count}.out
    if diff ${file}${count}.out ${file}${count}.ans > /dev/null ; then
	:
    else
    	echo "sample${count} : WA"
    fi

    let count++
done

echo "all finished"
