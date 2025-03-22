#!/usr/bin/env bash

BINARY_OPERATORS="+-*/"
BINARY_OPS_SIZE=${#BINARY_OPERATORS}
UNARY_OPERATORS="-+"
UNARY_OPS_SIZE=2
LOWER_LIMIT=-100
UPPER_LIMIT=100
NUMBERS=4

EXPRESSION=$(shuf -n 1 -i 0-$((UPPER_LIMIT - LOWER_LIMIT)))
while [ $NUMBERS -gt 1 ]; do
  NUM=$(shuf -n 1 -i 0-$((UPPER_LIMIT - LOWER_LIMIT)))
  NUM=$((NUM + $LOWER_LIMIT))
  if [ $NUM -lt 0 ]; then
    NUM="($NUM)"
  fi
  OP=$(shuf -n 1 -i 0-$((BINARY_OPS_SIZE - 1)))
  OP=${BINARY_OPERATORS:$OP:1}
  EXPRESSION=$EXPRESSION$OP$NUM
  NUMBERS=$((NUMBERS - 1))
done
echo $EXPRESSION
