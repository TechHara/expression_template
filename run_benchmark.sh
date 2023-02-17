for n in `seq 9`; do
    python3 create_vector.py ${n}000000 10 $n
done

for exec in naive lazy1 lazy2; do
    LOG=log_${exec}
    echo "$exec" > $LOG
    for n in `seq 9`; do
        build/$exec ${n}_input.bin ${n}_target.bin 2>&1 | grep time | awk '{print $5}' >> $LOG
    done
done


paste log_{naive,lazy1,lazy2} > result.tsv
rm -rf log_*
rm [1-9]_input.bin
rm [1-9]_target.bin