g++ -std=c++20 -O2 -DMeIoN test_st.cpp -o test_st

./test_st > testcase_st/out
echo "check st:"
if ! diff -b -B testcase_st/out testcase_st/std > /dev/null; then
    echo "wrong answer"
    break
else 
    echo "accept"
    rm -f testcase_st/out
fi