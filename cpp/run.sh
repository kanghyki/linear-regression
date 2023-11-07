#!/bin/bash

if [ $# -ne 3 ];
then
  echo "$0: Usage (csv_file_name) (x_name) (y_name)"
  exit 1
fi

make
./training $1 $2 $3

RESULT="result.csv"
./model ${RESULT}
