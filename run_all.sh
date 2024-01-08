#!/bin/bash

for file in large.txt medium.txt small.txt tinier.txt tiny.txt tst1.txt; do
    ./bankers < data/$file
done
