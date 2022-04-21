#include "trojanmap.h"
#include <limits.h>

void convert_string_to_lower(std::string &str) {
  for (auto &c : str) {
    c = tolower(c);
  }
}

// Util function to check if a graph is DAG or not
bool is_dag_util(std::string &location, std::vector<std::string> &visited, std::vector<std::string> &stack, std::unordered_map<std::string, std::vector<std::string>> &dependencies) {
  visited.push_back(location);
  stack.push_back(location);
  for (auto &dependency : dependencies[location]) {
    if (std::find(visited.begin(), visited.end(), dependency) == visited.end()) {
      if (!is_dag_util(dependency, visited, stack, dependencies)) {
        return false;
      }
    } else if (std::find(stack.begin(), stack.end(), dependency) != stack.end()) {
      return false;
    }
  }
  stack.pop_back();
  return true;
}

// Function to check if a graph is DAG or not
bool is_dag(std::vector<std::string> &locations, std::unordered_map<std::string, std::vector<std::string>> &dependencies) {
  std::vector<std::string> visited;
  std::vector<std::string> stack;
  for (auto &location : locations) {
    if (std::find(visited.begin(), visited.end(), location) == visited.end()) {
      if (!is_dag_util(location, visited, stack, dependencies)) {
        return false;
      }
    }
  }
  return true;
}

//-----------------------------------------------------
// TODO: Student should implement the following:
//-----------------------------------------------------
/**
 * GetLat: Get the latitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : latitude
 */
double TrojanMap::GetLat(const std::string& id) {
  if (data.find(id) == data.end()) {
    return -1;
  } 
  else {
    return data[id].lat;
  }
}

/**
 * GetLon: Get the longitude of a Node given its id. If id does not exist, return -1.
 * 
 * @param  {std::string} id : location id
 * @return {double}         : longitude
 */
double TrojanMap::GetLon(const std::string& id) { 
  if (data.find(id) == data.end()) {
    return -1;
  }
  else {
    return data[id].lon;
  }
}

/**
 * GetName: Get the name of a Node given its id. If id does not exist, return "NULL".
 * 
 * @param  {std::string} id : location id
 * @return {std::string}    : name
 */
std::string TrojanMap::GetName(const std::string& id) { 
  if (data.find(id) == data.end()) {
    return "NULL";
  }
  else {
    return data[id].name;
  }
}

/**
 * GetNeighborIDs: Get the neighbor ids of a Node. If id does not exist, return an empty vector.
 * 
 * @param  {std::string} id            : location id
 * @return {std::vector<std::string>}  : neighbor ids
 */
std::vector<std::string> TrojanMap::GetNeighborIDs(const std::string& id) {
  if (data.find(id) == data.end()) {
    return std::vector <std::string>();
  }
  else {
    return data[id].neighbors;
  }
}

/**
 * GetID: Given a location name, return the id. 
 * If the node does not exist, return an empty string. 
 *
 * @param  {std::string} name          : location name
 * @return {int}  : id
 */
std::string TrojanMap::GetID(const std::string& name) {
  std::string res = "";
  for (auto &it : data) {
    if (it.second.name == name) {
      res = it.first;
      break;
    }
  }
  return res;
}

/**
 * GetPosition: Given a location name, return the position. If id does not exist, return (-1, -1).
 *
 * @param  {std::string} name          : location name
 * @return {std::pair<double,double>}  : (lat, lon)
 */
std::pair<double, double> TrojanMap::GetPosition(std::string name) {
  std::pair<double, double> results(-1, -1);
  for (auto node : data) {
    if (node.second.name == name) {
      results.first = node.second.lat;
      results.second = node.second.lon;
    }
  }
  return results;
}


/**
 * CalculateEditDistance: Calculate edit distance between two location names
 * 
 */
int TrojanMap::CalculateEditDistance(std::string a, std::string b){
    std::vector <std::vector<int>> dp(a.size()+1, std::vector<int>(b.size()+1, 0));
    for (int i = 0; i <= a.size(); i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= b.size(); j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1]));
            }
        }
    }
    return dp[a.size()][b.size()];
}

/**
 * FindClosestName: Given a location name, return the name with smallest edit distance.
 *
 * @param  {std::string} name          : location name
 * @return {std::string} tmp           : similar name
 */
std::string TrojanMap::FindClosestName(std::string name) {
  std::string tmp = "";
  // Convert name to lower case
  convert_string_to_lower(name);
  int min_distance = INT_MAX;
  for (auto node : data) {
    // Handle empty strings
    if (node.second.name.size() == 0) {
      continue;
    }
    // Convert name to lower case
    std::string tmp_name = node.second.name;
    convert_string_to_lower(tmp_name);
    int distance = CalculateEditDistance(name, tmp_name);
    if (distance < min_distance) {
      min_distance = distance;
      tmp = node.second.name;
    }
  }
  return tmp;
}


/**
 * Autocomplete: Given a parital name return all the possible locations with
 * partial name as the prefix. The function should be case-insensitive.
 *
 * @param  {std::string} name          : partial name
 * @return {std::vector<std::string>}  : a vector of full names
 */
std::vector<std::string> TrojanMap::Autocomplete(std::string name){
  std::vector<std::string> results;
  convert_string_to_lower(name);
  for (auto node : data) {
      // Size of input should be smaller than the name of the node
      if (name.size() > node.second.name.size())
          continue;
      // Convert the name of the node to lower case
      std::string tmp = node.second.name;
      convert_string_to_lower(tmp);
      // If the prefix of the input is the same as the prefix of the node, add the node to the results
      if (tmp.find(name) == 0)
          results.push_back(node.second.name);
  }
  return results;
}

/**
 * CalculateDistance: Get the distance between 2 nodes. 
 * 
 * @param  {std::string} a  : a_id
 * @param  {std::string} b  : b_id
 * @return {double}  : distance in mile
 */
double TrojanMap::CalculateDistance(const std::string &a_id, const std::string &b_id) {
  // Do not change this function
  Node a = data[a_id];
  Node b = data[b_id];
  double dlon = (b.lon - a.lon) * M_PI / 180.0;
  double dlat = (b.lat - a.lat) * M_PI / 180.0;
  double p = pow(sin(dlat / 2),2.0) + cos(a.lat * M_PI / 180.0) * cos(b.lat * M_PI / 180.0) * pow(sin(dlon / 2),2.0);
  double c = 2 * asin(std::min(1.0,sqrt(p)));
  return c * 3961;
}

/**
 * CalculatePathLength: Calculates the total path length for the locations inside the vector.
 * 
 * @param  {std::vector<std::string>} path : path
 * @return {double}                        : path length
 */
double TrojanMap::CalculatePathLength(const std::vector<std::string> &path) {
  // Do not change this function
  double sum = 0;
  for (int i = 0;i < int(path.size())-1; i++) {
    sum += CalculateDistance(path[i], path[i+1]);
  }
  return sum;
}

/**
 * CalculateShortestPath_Dijkstra: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Use priority queue.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Dijkstra(
    std::string location1_name, std::string location2_name) {
  std::vector<std::string> path;

  // Initialize a map to store the distance from start to each node
  std::unordered_map<std::string, double> distance;

  // Initialize distances to infinity
  for (auto node : data) {
    distance[node.first] = INT_MAX;
  }

  // Initialize a map to store the previous node of each node
  std::unordered_map<std::string, std::string> previous;

  // Initialize a map to store the visited nodes
  std::unordered_map<std::string, bool> visited;

  // Initialize all visited noted to false
  for (auto node : data) {
    visited[node.first] = false;
  }

  // // Get the id of the start and goal locations
  // location1_name = FindClosestName(location1_name);
  // location2_name = FindClosestName(location2_name);

  // Get the id of the locations
  std::string location1_id = GetID(location1_name);
  std::string location2_id = GetID(location2_name);

  // If the start and goal locations are the same, return an empty path
  if (location1_id == location2_id) {
    return path;
  }

  // Initialize the priority queue
  std::priority_queue<std::pair<double, std::string>, 
                      std::vector<std::pair<double, std::string>>, 
                      std::greater<std::pair<double, std::string>>> pq;

  // Push the start location to the priority queue
  pq.push(std::make_pair(0, location1_id));

  // Initialize the distance of the start location to 0
  distance[location1_id] = 0;

  while (!pq.empty()) {
    // Get the node with the smallest distance
    std::string current_id = pq.top().second;
    pq.pop();
    // If the current node is the goal location, break
    if (current_id == location2_id) {
      break;
    }

    // If the current node has been visited, continue
    if (visited[current_id]) {
      continue;
    }

    // Mark the current node as visited
    visited[current_id] = true;

    // Get the neighbors of the current node
    std::vector<std::string> neighbors = GetNeighborIDs(current_id);

    // For each neighbor
    for (auto neighbor : neighbors) {
      // Get the distance from the current node to the neighbor
      double distance_to_neighbor = CalculateDistance(current_id, neighbor);

      // If the distance is smaller than the current distance, update the distance
      if (distance[current_id] + distance_to_neighbor < distance[neighbor]) {
        distance[neighbor] = distance[current_id] + distance_to_neighbor;
        previous[neighbor] = current_id;
        pq.push(std::make_pair(distance[neighbor], neighbor));
      }
    }
  }

  // Create the path
  std::string current_id = location2_id;
  while (current_id != location1_id) {
    path.push_back(current_id);
    current_id = previous[current_id];
  }

  // Add the start location to the path
  path.push_back(location1_id);
  
  // Reverse the path
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * CalculateShortestPath_Bellman_Ford: Given 2 locations, return the shortest path which is a
 * list of id. Hint: Do the early termination when there is no change on distance.
 *
 * @param  {std::string} location1_name     : start
 * @param  {std::string} location2_name     : goal
 * @return {std::vector<std::string>}       : path
 */
std::vector<std::string> TrojanMap::CalculateShortestPath_Bellman_Ford(
    std::string location1_name, std::string location2_name){
  std::vector<std::string> path;
  
  // Initialize a map to store the distance from start to each node
  std::unordered_map<std::string, double> distance;

  // Initialize a map to store the previous node of each node 
  std::unordered_map<std::string, std::string> previous;

  // Initialize distances to infinity
  for (auto node : data) {
    distance[node.first] = INT_MAX;
  }

  // Get the id of the locations
  std::string location1_id = GetID(location1_name);
  std::string location2_id = GetID(location2_name);

  // If the start and goal locations are the same, return an empty path
  if (location1_id == location2_id) {
    return path;
  }

  // Initialize the distance of the start location to 0
  distance[location1_id] = 0;
  int iterations = data.size()-1;

  // Traverse all edges
  for (int i = 0; i < iterations; i++) {
    bool STOP = true;
    for (auto node: data) {
      // Get neighbors of the current node
      std::vector<std::string> neighbors = GetNeighborIDs(node.first);
      for (auto neighbor: neighbors) {
        // Get the distance from the current node to the neighbor
        double distance_to_neighbor = CalculateDistance(node.first, neighbor);
        // If the distance is smaller than the current distance, update the distance
        if (distance[node.first] + distance_to_neighbor < distance[neighbor]) {
          distance[neighbor] = distance[node.first] + distance_to_neighbor;
          previous[neighbor] = node.first;
          STOP = false;
        }
      }
    }
    if (STOP) {
      break;
    }
  }
  
  // Create the path
  std::string current_id = location2_id;
  while (current_id != location1_id) {
    path.push_back(current_id);
    current_id = previous[current_id];
    }

  // Add the start location to the path
  path.push_back(location1_id);
  
  // Reverse the path
  std::reverse(path.begin(), path.end());
  return path;
}

/**
 * Travelling salesman problem: Given a list of locations, return the shortest
 * path which visit all the places and back to the start point.
 *
 * @param  {std::vector<std::string>} input : a list of locations needs to visit
 * @return {std::pair<double, std::vector<std::vector<std::string>>} : a pair of total distance and the all the progress to get final path
 */
std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Brute_force(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_Backtracking(
                                    std::vector<std::string> location_ids) {
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

std::pair<double, std::vector<std::vector<std::string>>> TrojanMap::TravellingTrojan_2opt(
      std::vector<std::string> location_ids){
  std::pair<double, std::vector<std::vector<std::string>>> records;
  return records;
}

/**
 * Given CSV filename, it read and parse locations data from CSV file,
 * and return locations vector for topological sort problem.
 *
 * @param  {std::string} locations_filename     : locations_filename
 * @return {std::vector<std::string>}           : locations 
 */
std::vector<std::string> TrojanMap::ReadLocationsFromCSVFile(std::string locations_filename){
  std::vector<std::string> location_names_from_csv;
  // Open the file
  std::fstream locations_file;
  locations_file.open(locations_filename, std::ios::in);
  std::string line;

  // Call getline to ignore the header
  getline(locations_file, line);

  // Read the rest of the lines
  while (getline(locations_file, line)) {
    std::stringstream ss(line);
    std::string location_name;
    std::getline(ss, location_name);
    location_names_from_csv.push_back(location_name);
  }
  return location_names_from_csv;
}

/**
 * Given CSV filenames, it read and parse dependencise data from CSV file,
 * and return dependencies vector for topological sort problem.
 *
 * @param  {std::string} dependencies_filename     : dependencies_filename
 * @return {std::vector<std::vector<std::string>>} : dependencies
 */
std::vector<std::vector<std::string>> TrojanMap::ReadDependenciesFromCSVFile(std::string dependencies_filename){
  std::vector<std::vector<std::string>> dependencies_from_csv;
  // Open the file
  std::fstream dependencies_file;
  dependencies_file.open(dependencies_filename, std::ios::in);
  std::string line;

  // Call getline to ignore the header
  getline(dependencies_file, line);

  // Read the rest of the lines
  while (getline(dependencies_file, line)) {
    std::stringstream ss(line);
    std::string dependency_from;
    std::string dependency_to;
    std::getline(ss, dependency_from, ',');
    std::getline(ss, dependency_to);
    std::vector<std::string> dependency = {dependency_from, dependency_to};
    dependencies_from_csv.push_back(dependency);
  }

  return dependencies_from_csv;
}

/**
 * DeliveringTrojan: Given a vector of location names, it should return a sorting of nodes
 * that satisfies the given dependencies. If there is no way to do it, return a empty vector.
 *
 * @param  {std::vector<std::string>} locations                     : locations
 * @param  {std::vector<std::vector<std::string>>} dependencies     : prerequisites
 * @return {std::vector<std::string>} results                       : results
 */
std::vector<std::string> TrojanMap::DeliveringTrojan(std::vector<std::string> &locations,
                                                     std::vector<std::vector<std::string>> &dependencies){
  std::vector<std::string> result;

  // Map to store the visited nodes
  std::unordered_map<std::string, bool> visited;

  // Map to store the dependencies
  std::unordered_map<std::string, std::vector<std::string>> dependency_map;

  // Initialize visited map
  for (auto location : locations) {
    visited[location] = false;
  }

  // Create edge map
  for (auto &dependency : dependencies) {
    dependency_map[dependency[0]].push_back(dependency[1]);
  }

  // Check if graph is DAG or not
  if (!is_dag(locations, dependency_map)) {
    return result;
  }

  // Call topological sort helper function on unvisited nodes
  for (auto location : locations) {
    if (!visited[location]) {
      TopologicalSort(location, dependency_map, visited, result);
    }
  }
  // Reverse the result
  std::reverse(result.begin(), result.end());
  return result;                                                     
}

// Helper function for topological sort
void TrojanMap::TopologicalSort(std::string &location,
                                std::unordered_map<std::string, std::vector<std::string>> &dependency_map,
                                std::unordered_map<std::string, bool> &visited,
                                std::vector<std::string> &result) {

    // Mark the dependency as visited
    visited[location] = true;

  // Iterate through all the dependencies
  for (auto &dependency : dependency_map[location]) {
    // If the dependency is not visited, call topological sort on it
    if (!visited[dependency]) {
      TopologicalSort(dependency, dependency_map, visited, result);
    }
  }
  // Add the location to the result
  result.push_back(location);
}

/**
 * inSquare: Give a id retunr whether it is in square or not.
 *
 * @param  {std::string} id            : location id
 * @param  {std::vector<double>} square: four vertexes of the square area
 * @return {bool}                      : in square or not
 */
bool TrojanMap::inSquare(std::string id, std::vector<double> &square) {
  Node n = data[id];
  if (n.lon > square[0] && n.lon < square[1] && n.lat < square[2] && n.lat > square[3]) {
    return true;
  }
  return false;
}

/**
 * GetSubgraph: Give four vertexes of the square area, return a list of location ids in the squares
 *
 * @param  {std::vector<double>} square         : four vertexes of the square area
 * @return {std::vector<std::string>} subgraph  : list of location ids in the square
 */
std::vector<std::string> TrojanMap::GetSubgraph(std::vector<double> &square) {
  // include all the nodes in subgraph
  std::vector<std::string> subgraph;
  // Iterate through all the nodes
  for (auto &n: data) {
    // Check if the node is in the square
    if (inSquare(n.first, square)) {
      subgraph.push_back(n.first);
    }
  }
  return subgraph;
}

/**
 * Cycle Detection: Given four points of the square-shape subgraph, return true if there
 * is a cycle path inside the square, false otherwise.
 * 
 * @param {std::vector<std::string>} subgraph: list of location ids in the square
 * @param {std::vector<double>} square: four vertexes of the square area
 * @return {bool}: whether there is a cycle or not
 */

bool TrojanMap::CycleDetectionHelper(std::string &current_point,
                                      std::unordered_map<std::string, bool> &visited, 
                                      std::string &parent,
                                      std::vector<double> &square){

  // Visit node only if it is in the square
  if (inSquare(current_point, square)) {
    // Mark the current node as visited
    visited[current_point] = true;


    // Find all the vertices which are not visited and are adjacent to the current node
    std::vector<std::string> neighbors = GetNeighborIDs(current_point);
    for (auto neighbor: neighbors){
      // If the neighbor is not visited, call the helper function recursively
      if (!visited[neighbor] && inSquare(neighbor, square)) {
        if (CycleDetectionHelper(neighbor, visited, current_point, square)){
          return true;
        }
      }
      // If neighbor is visited and is not parent of the current node, there is a cycle
      else if (visited[neighbor] && neighbor != parent){
        return true;
      }
    }
  }
  return false;
}

bool TrojanMap::CycleDetection(std::vector<std::string> &subgraph, std::vector<double> &square) {
  // Create a map to store the visited nodes
  std::unordered_map<std::string, bool> visited;

  std::cout << "subgraph size: " << subgraph.size() << std::endl;

  // Initialize visited map
  for (auto points : subgraph) {
    visited[points] = false;
  }

  // Call the recursive helper
  // function to detect cycle

  std::string parent = "NULL";

  for (auto points : subgraph) {
    // Don't recur for points if
    // it is already visited
    if (!visited[points]) {
      if (CycleDetectionHelper(points, visited, parent, square)) {
        return true;
      }
    }
  }
  return false;
}

/**
 * FindNearby: Given a class name C, a location name L and a number r, 
 * find all locations in class C on the map near L with the range of r and return a vector of string ids
 * 
 * @param {std::string} className: the name of the class
 * @param {std::string} locationName: the name of the location
 * @param {int} r: search radius
 * @param {int} k: search numbers
 * @return {std::vector<std::string>}: location name that meets the requirements
 */
std::vector<std::string> TrojanMap::FindNearby(std::string attributesName, std::string name, double r, int k) {
  std::vector<std::string> res;
  return res;
}

/**
 * CreateGraphFromCSVFile: Read the map data from the csv file
 * 
 */
void TrojanMap::CreateGraphFromCSVFile() {
  // Do not change this function
  std::fstream fin;
  fin.open("src/lib/data.csv", std::ios::in);
  std::string line, word;

  getline(fin, line);
  while (getline(fin, line)) {
    std::stringstream s(line);

    Node n;
    int count = 0;
    while (getline(s, word, ',')) {
      word.erase(std::remove(word.begin(), word.end(), '\''), word.end());
      word.erase(std::remove(word.begin(), word.end(), '"'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '{'), word.end());
      word.erase(std::remove(word.begin(), word.end(), '}'), word.end());
      if (count == 0)
        n.id = word;
      else if (count == 1)
        n.lat = stod(word);
      else if (count == 2)
        n.lon = stod(word);
      else if (count == 3)
        n.name = word;
      else {
        word.erase(std::remove(word.begin(), word.end(), ' '), word.end());
        if (isalpha(word[0]))
          n.attributes.insert(word);
        if (isdigit(word[0]))
          n.neighbors.push_back(word);
      }
      count++;
    }
    data[n.id] = n;
  }
  fin.close();
}
