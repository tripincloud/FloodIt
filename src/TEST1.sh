c=0
i=$1
while [[ c -lt 10 ]]
do
    ./Flood-It_Partie1 $((i)) 25 1 1 1 0 >> exo1_dim_$((i)).csv
    c=$((c+1))
done;
