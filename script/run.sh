#!/usr/bin/bash

cd ..
echo "version number ? (1,2 or 3)"
read x
echo "number of tests ? (less than 10 please)"
read N

echo "compiling itineraries_v$x.cpp ..."
g++ -o executable itineraries_v$x.cpp MST.cpp

export LC_NUMERIC="en_US.UTF-8"
TIMEFORMAT=%R

DIR="time/time_v$x.csv"

echo -n "Input" > $DIR
for test_number in $(seq 1 $N)
do
  echo -n ",$test_number" >> $DIR
done
printf "\n" >> $DIR

for i in input/*.in
do
  i=$(basename $i)
  i=${i%".in"}
  echo "testing $i..."
  echo -n "$i" >> $DIR
  for run in $(seq 1 $N)
  do
    echo -n "," >> $DIR
    duration=$( { time ./executable < input/$i".in" > output/$i".out" ;} 2>&1)
    echo -n "$duration" >> $DIR
    echo "$duration"
  done
  printf "\n" >> $DIR
done

rm executable

echo "Done! Check $DIR for time report"
