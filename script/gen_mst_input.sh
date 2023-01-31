#!/usr/bin/bash
cd ..

if [ ! -d "input_mst" ]; then
  mkdir input_mst
fi

g++ -o executable  gen_mst_input.cpp MST.cpp

for i in input/*.in; do
  i=$(basename $i)
  echo "running $i..."
  ./executable < input/$i > input_mst/$i
done

rm executable

echo "Done!"
