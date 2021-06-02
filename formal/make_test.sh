#!/bin/bash

g++ -g createEdgeVector.cpp -o createEdge.o
g++ -g createGraphVector.cpp -o createGraph.o
g++ -g prim.cpp -o prim.o
g++ -g kruskal.cpp -o kruskal.o
g++ -g getaverage.cpp -o getaverage.o

mkdir -p testData
mkdir -p recordData
for n in `seq 20000 1000 20000` 
do
	tmp=`expr $n - 1`
	echo $tmp
	sum=`expr $n \* $tmp`
	sum=`expr $sum / 2`
	echo $sum
	sh -c './createEdge.o '$sum''
	for filename in equalEdge.txt permutationEdge.txt randomEdge.txt
	do
		sh -c './createGraph.o '$filename' '$n' '$sum''
        for graph in 0 $tmp
		do
			echo "" >  ./testData/tmp.txt
			echo $graph 'prim'
			for T in `seq 0 9`
			do
                echo 'test' $T
				sh -c './prim.o < ./'$n'average/graph'$graph'.txt >> ./testData/tmp.txt'
			done
			sh -c './getaverage.o > ./recordData/prim_'$n'_'$filename'_'$graph'.txt'
		    echo $graph kruskal
            echo "" > ./testData/tmp.txt	
			for T in `seq 0 9`
			do
                echo 'test' $T
				sh -c './kruskal.o < ./'$n'average/graph'$graph'.txt >> ./testData/tmp.txt'
			done
			sh -c './getaverage.o > ./recordData/kruskal_'$n'_'$filename'_'$graph'.txt'
        done
	done
done
