#!/usr/bin/bash


for i in input/*.in
do
  i=$(basename $i)
  i=${i%".in"}
  
  echo "testing $i..."
  printf "time for $i:" >> time.txt
  { time ./executable < input/$i".in" > output/$i".out" ;} 2>>time.txt
  printf "\n" >> time.txt
done

echo "Done! Check time.txt for time report"
