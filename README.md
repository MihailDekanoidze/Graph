# Graph researcher

The project represents two programms, which based on Dejkstra algorithm.
The first is searching the best way with the lowest narrow place among all between two vertex.
The second is searching a vertex with the lowest number of vertex, which can be visited in set range from source vertex.

## How to start:
To start a programm you need launch make in terminal in programm's directory:
```
make
```
Once makefile has done it, programm can be run:  
```
make run
```
Let's go to enter this graph:

![Example graph](/images/abcd_graph.png)

Then enter a count all of links in graph
```
Enter links number: 5
```
And with each new line enter link in this format:

|VERTEX1|  |VERTEX2|  |DISTANCE|

The |VERTEX1| is a letter - name of the first vertex, |VERTEX2| - name of the second vertex (is letter too) and |DISTANCE| is a non-negative integer, less than 10^10.
```
a b 1
a c 10
b d 10
c d 3
b c 2
```
### The first programm

Then enter the start vertex:
```
Start vertex: a
```
The end vertex:
```
End vertex: d
```
The answer:
```
Path :
a -> b -> c -> d
3
```
### The second programm

Then enter the radius:
```
Enter the mileage: 5
```
The answer:
```
The city with lowest links in range 5 is: d
```
