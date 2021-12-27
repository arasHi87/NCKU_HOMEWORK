prob=26
tc=04

# cp ../hw${prob}/sol.c f74094716_hw${prob}.c
gcc -Wall -Wno-unused-variable -std=c11 f74094716_hw${prob}.c -lm

for i in `seq 01 $tc`
do
    idx=$(printf "%02d" $i)
    rm -rf out
    ./a.out < ../hw${prob}/input_${idx}.txt > out
    diff -w out ../hw${prob}/output_${idx}.txt
    echo "prob ${prob} test case ${idx} done"
done