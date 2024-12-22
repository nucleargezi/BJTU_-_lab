g++ -std=c++20 -O2 -DMeIoN test_gra.cpp -o test_gra

./test_gra > testcase/out
if ! diff -b -B testcase/out testcase/std_gra > /dev/null; then
    echo "wrong answer"
    break
else 
    echo "accept"
    rm -f testcase/out
fi