#!/bin/bash

i=1
while [ $i -le 1000000 ]
do
	./ex17 db s $i sdfkjsldkfjalksdf adfaklsfjlas
	i=$(($i + 1))
done
