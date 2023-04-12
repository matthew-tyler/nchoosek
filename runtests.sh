#!/bin/bash

# Compile counting.c
gcc counting.c -o counting

# Check if the compilation was successful
if [ $? -ne 0 ]; then
  echo "Compilation failed"
  exit 1
fi

# Run the compiled counting program with input file 2.in
./counting < 2.in > 2.out

# Diff the output with the expected output
diff 2.out 2.ans > /dev/null

# Check if diff was successful
if [ $? -eq 0 ]; then
  echo "2.in: PASS"
else
  echo "2.in: FAIL"
fi