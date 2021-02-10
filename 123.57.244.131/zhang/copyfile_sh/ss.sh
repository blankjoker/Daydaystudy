#!/bin/bash

var=0

while [ $var -lt 1000 ]
do
    echo "create $var.c successful"
    ((var++))
    touch $var.c
done
