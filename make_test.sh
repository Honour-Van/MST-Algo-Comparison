g++ -g createEdge.cpp -o createEdge.o
g++ -g createGraph.cpp -o createGraph.o
g++ -g prim.cpp -o prim.o
g++ -g kruskal.cpp -o kruskal.o
g++ -g getaverage.cpp -o getaverage.o
g++ -g primHeap.cpp -o primHeap.o

mkdir -p testData
mkdir -p recordData-pernode
mkdir -p recordData-average
# for n in 1000 2000 5000 10000 
for n in 5000 10000
do
    tmp=`expr $n - 1`
    echo $tmp
    sum=`expr $n \* $tmp`
    sum=`expr $sum / 2`
    mod=`expr $n / 50`
    echo $mod
    sh -c './createEdge.o '$sum''
    for filename in equalEdge.txt permutationEdge.txt randomEdge.txt
    do  
        sh -c './createGraph.o '$filename' '$n' '$sum''
        for graph in `seq 0 2 300`
        do  
            echo "" >  ./testData/tmp.txt
            echo $graph 'prim'
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './prim.o < ./'$n'pernode/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-pernode/prim_'$n'_'$filename'_'$graph'.txt'
            echo $graph kruskal
            echo "" > ./testData/tmp.txt    
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './kruskal.o < ./'$n'pernode/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-pernode/kruskal_'$n'_'$filename'_'$graph'.txt'
            echo "" >  ./testData/tmp.txt
            echo $graph 'primHeap'
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './primHeap.o < ./'$n'pernode/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-pernode/primHeap_'$n'_'$filename'_'$graph'.txt'
            
            echo "" >  ./testData/tmp.txt
            echo $graph 'prim'
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './prim.o < ./'$n'average/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-average/prim_'$n'_'$filename'_'$graph'.txt'
            echo $graph kruskal
            echo "" > ./testData/tmp.txt    
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './kruskal.o < ./'$n'average/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-average/kruskal_'$n'_'$filename'_'$graph'.txt'
            echo "" >  ./testData/tmp.txt
            echo $graph 'primHeap'
            for T in `seq 0 9`
            do  
                echo 'test' $T
                sh -c './primHeap.o < ./'$n'average/graph'$graph'.txt >> ./testData/tmp.txt'
            done
            sh -c './getaverage.o > ./recordData-average/primHeap_'$n'_'$filename'_'$graph'.txt'
        done
    done
    rm -r $n* 
done

