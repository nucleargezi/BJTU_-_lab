g++ -std=c++20 -O2 -DMeIoN test_SLR.cpp -o test_SLR

for i in {0..3}; do
    echo "test: $i"
    ./test_SLR < testcase/in$i > testcase/out$i
    if ! diff -b -B testcase/out$i testcase/std$i > /dev/null; then
        echo "wrong answer"
        break
    else 
        echo "accept"
        rm -f testcase/out$i
    fi
done