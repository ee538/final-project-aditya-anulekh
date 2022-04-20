# Group Members
Aditya Anulekh Mantri - adityaan@usc.edu - 8049574464
Aditi Bodhankar - bodhanka@usc.edu - 9323549368

# Phase 1

## Autocomplete
* Convert all alphabets to lower case
* Iterate through all the points in the map
* If length of input is greater than the current name, skip the word (Ex: input - Starbucks 1, current - Starbucks)
* Convert name to lower case
* Find the input in the current name using `std::find`. If input is found in current name, add that to the result vector

## Get Position
* Iterate through all the points in the map and return the latitude and longitude of the matched name
* If no match is found return (-1, -1)
* In the case where no match is found, find the closest name to the entered input

## Find Closest Name
* This function calls `CalculateEditDistance` internally on every name in the map data
* The function skips entries that are empty strings
* The name with the lowest edit distance is returned as a string from this function

## Calculate Edit Distance
* Initialize a matrix `dp` of size (`a.size()` x `b.size()`) with zeros
* Intialize the first row and first column of the above matrix with 0 to `a.size()` and 0 to `b.size()`. This is to handle the base cases

    * a = "", b = "abc"
    * a = "abc", b = ""

* Update all the elements of `dp` according to the following rules

    * If the characters at index `i` and `j` in `a` and `b` match, dp[i][j] = dp[i-1][j-1]
    * If the characters at index `i` and `j` don't match in `a` and `b` dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])

* Finally return the value at `dp[a.size()][b.size()]`

## Calculate Shortest Path
* Dijkstra's Algorithm: 
    * Initialized a map `distance` to store the distance from start to each node
    * Initialized the distances to infinity
    * Initialized a map `previous`to store the previous node of each node
    * Initialized a map `visited` to all `False`to store the visited nodes
    * Then obtained the id of the source and the destination locations
    * Corner case: If the start and goal locations are the same, returned an empty path
    * Initialized a priority queue to get the closest neighbor for every unvisited node. the function `CalculateDistance` is used to calculate the distances between the neighbors and the current node to update the closest neighbor
    * Once the closest neighbor is obtained it is appended into the `previous` map defined as above
    * Finally the path is created using the nodes from the `previous` map

* Bellman Ford Algorithm:
    In this algorithm, a shortest path is calculated between all the nodes
    * Similar to the above algorithm, two maps for `distance` and `previous` are initialized 
    * The distances of all the nodes are initialized to be infinity
    * Then obtained the id of the source and the destination locations
    * Corner case: If the start and goal locations are the same, returned an empty path
    * The distance of the source is initialized to 0. As the algorithm traverses over all edge possibilities (minimum number of edges needed to find the shortest path), we calculate the shortest distance of every node from all its neighbors. 
    * An additional STOP sign is added into the algorithm to hault the program once the minimum distances do not vary with more number of edges.
    * All the closest neighbors are then added into the `previous` map
    * Since, this algorithm calculates the shortest path between any two nodes, it has a longer run time than Dijkstra's algorithm. 
