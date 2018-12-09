#!/bin/bash
points=0
while getopts "p:" opt; do
    case $opt in
	p)
	    points=$OPTARG
	    ;;
	\?)
	    echo "Invalid option: -$OPTARG" >&2
	    exit 1
	    ;;
	:)
	    echo "Option -$OPTARG requires an argument." >&2
	    exit 1
	    ;;
    esac
done

count=1
inCircle=0
while [ "$count" -le $points ]
do
    x=$(awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}')
    x=$(echo "$x + 0.000001" | bc)
    y=$(awk -v seed=$RANDOM 'BEGIN{srand(seed);print rand()}')
    y=$(echo "$y + 0.000001" | bc)
    x2=$(echo "$x*$x" | bc)
    y2=$(echo "$y*$y" | bc)
    sum=$(echo "$x2 + $y2" | bc)
    dist=$(echo "sqrt($sum)" | bc)
    if (( $(echo "$dist <= 1" | bc -l) )); then
	let "inCircle += 1"
    fi
    let "count += 1"
    let "points += 1"
done
divided=$(echo "scale=4; $inCircle / $points" | bc -l)
pi=$(echo "$divided * 4.0" | bc)
echo "pi = $pi"
