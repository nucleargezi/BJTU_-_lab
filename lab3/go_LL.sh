g++ -std=c++20 -O2 -DMeIoN test_LL.cpp -o test_LL

for i in {0..3}; do
    ./test_LL < testcase/in$i > testcase/out$i
    echo "test: $i"
    if ! diff -b -B testcase/out$i testcase/std$i > /dev/null; then
        echo "wrong answer"
        break
    else 
        echo "accept"
        rm -f testcase/out$i
    fi
done