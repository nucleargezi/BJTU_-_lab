g++ -std=c++20 -O2 -DMeIoN test_mp.cpp -o test_mp

./test_mp > testcase_mp/out
if ! diff -b -B testcase_mp/out testcase_mp/std > /dev/null; then
    echo "wrong answer"
    break
else 
    echo "accept"
    rm -f testcase_mp/out
fi