#!/bin/bash

for i in {1..1000}
do
    nc -zv 127.0.0.1 4242 &
done
