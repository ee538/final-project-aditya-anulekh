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