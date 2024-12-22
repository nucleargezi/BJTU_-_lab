g++ -std=c++20 -O2 -DMeIoN test_opp.cpp -o test_opp

for i in {0..3}; do
    echo "test: $i"
    ./test_opp < testcase/in$i > testcase/out$i
    if ! diff -b -B testcase/out$i testcase/std$i > /dev/null; then
        echo "wrong answer"
        break
    else 
        echo "accept"
        rm -f testcase/out$i
    fi
done