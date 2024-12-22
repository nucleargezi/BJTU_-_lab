g++ -std=c++20 test_token_solver.cpp -o test_token_solver

cnt = 0

for i in {0..3}; do
    ./test_token_solver < testcase/test$i > meion_my_out$i
    ((cnt++))
    echo "test: $cnt"
    if ! diff -b -B meion_my_out$i testcase/std$i > /dev/null; then
        echo "wrong answer"
        break
    else 
        echo "accept"
        rm -f meion_my_out$i
    fi
done