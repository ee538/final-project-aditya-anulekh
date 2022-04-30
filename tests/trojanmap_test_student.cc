#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "src/lib/trojanmap.h"

using ::testing::UnorderedElementsAreArray;

TEST(TrojanMapStudentTest, GetLatLon) {
  TrojanMap m;
  std::vector<std::string> v = {"6816193772", "6813416126", "6813416125"};
  EXPECT_EQ(34.0302951, m.GetLat("122659207"));
  EXPECT_EQ(-118.2857237, m.GetLon("122659207"));
  EXPECT_EQ(v, m.GetNeighborIDs("122659207"));
  EXPECT_EQ("Crosswalk", m.GetName("122659207"));
  EXPECT_EQ("122659207", m.GetID("Crosswalk"));
}

TEST(TrojanMapStudentTest, Autocomplete_Test1) {
  TrojanMap m;
  // Test the simple case
  auto names1 = m.Autocomplete("Tar");
  std::unordered_set<std::string> gt1 = {"Target"}; // groundtruth for "Tar"
  int success1 = 0;
  for (auto& n: names1) {
    EXPECT_EQ(gt1.count(n) > 0, true) << n + " is not in gt.";
    if (gt1.count(n) > 0){
      success1++;
      }
  }

  // Test the case for lower case
  auto names2 = m.Autocomplete("tar");
  std::unordered_set<std::string> gt2 = {"Target"}; // groundtruth for "Tar"
  int success2 = 0;
  for (auto& n: names2) {
    EXPECT_EQ(gt2.count(n) > 0, true) << n + " is not in gt.";
    if (gt2.count(n) > 0){
      success2++;
      }
  }

  // Test the case for lower case
  auto names3 = m.Autocomplete("tAr");
  std::unordered_set<std::string> gt3 = {"Target"}; // groundtruth for "Tar"
  int success3 = 0;
  for (auto& n: names2) {
    EXPECT_EQ(gt3.count(n) > 0, true) << n + " is not in gt.";
    if (gt3.count(n) > 0){
      success3++;
      }
  }

  auto names4 = m.Autocomplete("Ven");
  std::unordered_set<std::string> gt4 = {"Venice & Broadway", "Venice & Olive", "Venice & Hill",
  "Venice & Grand 1", "Venice & Grand", "Venice & Hope", "Venice & Flower", "Venice & Oak", "Venice & Oak 1", 
  "Venice & Figueroa", "Venice & Figueroa 1"}; // groundtruth for "Ven"
  int success4 = 0;
  for (auto& n: names4) {
    EXPECT_EQ(gt4.count(n) > 0, true) << n + " is not in gt.";
    if (gt4.count(n) > 0){
      success4++;
      }
  }

  // Test the case for lower case
  auto names5 = m.Autocomplete("VeN");
  std::unordered_set<std::string> gt5 = {"Venice & Broadway", "Venice & Olive", "Venice & Hill",
  "Venice & Grand 1", "Venice & Grand", "Venice & Hope", "Venice & Flower", "Venice & Oak", "Venice & Oak 1", 
  "Venice & Figueroa", "Venice & Figueroa 1"}; // groundtruth for "VeN"
  int success5 = 0;
  for (auto& n: names5) {
    EXPECT_EQ(gt5.count(n) > 0, true) << n + " is not in gt.";
    if (gt5.count(n) > 0){
      success5++;
      }
  }

  // Test the case for lower case
  auto names6 = m.Autocomplete("star");
  std::unordered_set<std::string> gt6 = {"Starbucks", "Starbucks 1", "Starbucks 2", "Starbucks 3"}; // groundtruth for "Tar"
  int success6 = 0;
  for (auto& n: names6) {
    EXPECT_EQ(gt6.count(n) > 0, true) << n + " is not in gt.";
    if (gt6.count(n) > 0){
      success6++;
      }
  }

  // Test the case for lower case
  auto names7 = m.Autocomplete("trAD");
  std::unordered_set<std::string> gt7 = {"Trader Joes"}; // groundtruth for "Tar"
  int success7 = 0;
  for (auto& n: names7) {
    EXPECT_EQ(gt7.count(n) > 0, true) << n + " is not in gt.";
    if (gt7.count(n) > 0){
      success7++;
      }
  }

}

// Test FindPosition function
TEST(TrojanMapStudentTest, FindPosition_Test1) {
  TrojanMap m;
  
  // Test Chick-fil-A
  auto position = m.GetPosition("Insomnia Cookies");
  std::pair<double, double> gt1(34.0250102,-118.2852990); // groundtruth for "Insomnia Cookies"
  EXPECT_EQ(position, gt1);
  // Test Ralphs
  position = m.GetPosition("Venice & Flower");
  std::pair<double, double> gt2(34.0370120,-118.2690326); // groundtruth for "Venice & Flower"
  EXPECT_EQ(position, gt2);
  // Test Target
  position = m.GetPosition("CVS Pharmacy");
  std::pair<double, double> gt3(34.0234847,-118.2793109); // groundtruth for "CVS Pharmacy"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXXXXXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
  
  position = m.GetPosition("KFC");
  std::pair<double, double> gt5(34.0260723,-118.2780288); // groundtruth for "KFC"
  EXPECT_EQ(position, gt5);

  position = m.GetPosition("7-Eleven");
  std::pair<double, double> gt6(34.0273247,-118.2572280); // groundtruth for "7-Eleven"
  EXPECT_EQ(position, gt6);
  
  position = m.GetPosition("Starbucks");
  std::pair<double, double> gt7(34.0390615,-118.2611170); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt7);
  
  position = m.GetPosition("Chevron 1");
  std::pair<double, double> gt8(34.0336409,-118.2620798); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt8);

  position = m.GetPosition("Fashion District");
  std::pair<double, double> gt9(34.0366220,-118.2590687); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt9);

  position = m.GetPosition("Olive & Pico");
  std::pair<double, double> gt10(34.0380880,-118.2632569); // groundtruth for "Starbucks"
  EXPECT_EQ(position, gt10);

}

// Test CalculateEditDistance function
TEST(TrojanMapStudentTest, CalculateEditDistance_Test1) {
  TrojanMap m;
  EXPECT_EQ(m.CalculateEditDistance("Target", ""), 6);
  EXPECT_EQ(m.CalculateEditDistance("Target", "Tagret"), 2);
  EXPECT_EQ(m.CalculateEditDistance("Target", "Targ"), 2);
  EXPECT_EQ(m.CalculateEditDistance("Target", "USC Credit Union"), 14);
  EXPECT_EQ(m.CalculateEditDistance("", "USC Credit Union"), 16);
  EXPECT_EQ(m.CalculateEditDistance("", ""), 0);
  EXPECT_EQ(m.CalculateEditDistance("   ", ""), 3);
  EXPECT_EQ(m.CalculateEditDistance("USC Credit Union", "Olive & Pico"), 13);
  EXPECT_EQ(m.CalculateEditDistance("Venice & Broadway", "Venice & Broadway"), 0);
  EXPECT_EQ(m.CalculateEditDistance("#@%&*", "  y"), 5);
  EXPECT_EQ(m.CalculateEditDistance("Roplhs", "Martin Luther King Junior & Broadway 1"), 37);
}

// Test FindClosestName function
TEST(TrojanMapStudentTest, FindClosestName_Test1) {
  TrojanMap m;
  EXPECT_EQ(m.FindClosestName("Rolfs"), "Ross");
  EXPECT_EQ(m.FindClosestName("Starducks"), "Starbucks");
  EXPECT_EQ(m.FindClosestName("CBS Farmasy"), "CVS Pharmacy");
  EXPECT_EQ(m.FindClosestName("Chose"), "Chase");
  EXPECT_EQ(m.FindClosestName("Doolse"), "Dulce");
  EXPECT_EQ(m.FindClosestName("Satrducks"), "Starbucks");
  EXPECT_EQ(m.FindClosestName("Tagret"), "Target");
  EXPECT_EQ(m.FindClosestName("Byank of Amrica"), "Bank of America");
  EXPECT_EQ(m.FindClosestName("Soobvay"), "Subway");
  EXPECT_EQ(m.FindClosestName("MacDonals"), "McDonalds");
  EXPECT_EQ(m.FindClosestName("Bava"), "CAVA");
  EXPECT_EQ(m.FindClosestName("Moneybird"), "Honeybird");
}

// Test TopologicalSort function
TEST(TrojanMapStudentTest, TopologicalSort) {
  TrojanMap m;
  std::vector <std::string> res = { "Ralphs", "Chick-fil-A", "KFC" };
  std::vector <std::string> locations = {"Ralphs", "KFC", "Chick-fil-A"};
  std::vector <std::vector<std::string>> dependencies = {{"Ralphs", "Chick-fil-A"}, {"Ralphs", "KFC"}, {"Chick-fil-A", "KFC"}};
  std::vector <std::vector<std::string>> dependencies1 = {};
  EXPECT_EQ(m.DeliveringTrojan(locations, dependencies), res);
  // EXPECT_EQ(m.DeliveringTrojan(locations, dependencies1), res);
}

// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapStudentTest, CalculateShortestPath_Dijkstra){
  TrojanMap m;
  // TEST1
  // Test from Ralphs to Target
  auto path1 = m.CalculateShortestPath_Dijkstra("Ralphs", "Target");
  std::vector<std::string> gt1{
      "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469",
      "6813416131","7645318201","6813416130","6813416129","123318563","452688940",
      "6816193777","123408705","6816193774","452688933","452688931","123230412",
      "6816193770","6787470576","4015442011","6816193692","6816193693","6816193694",
      "4015377691","544693739","6816193696","6804883323","6807937309","6807937306",
      "6816193698","4015377690","4015377689","122814447","6813416159","6813405266",
      "4015372488","4015372487","6813405229","122719216","6813405232","4015372486",
      "7071032399","4015372485","6813379479","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path1) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt1) << "miles" << std::endl;
  EXPECT_EQ(path1, gt1);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path1 = m.CalculateShortestPath_Dijkstra("Target", "Ralphs");
  std::reverse(gt1.begin(),gt1.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path1) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt1) << "miles" << std::endl;
  EXPECT_EQ(path1, gt1);

  // TEST2
  // Test from Chick-fil-A to CVS Pharmacy
  auto path2 = m.CalculateShortestPath_Dijkstra("Chick-fil-A", "CVS Pharmacy");
  std::vector<std::string> gt2{
      "4547476733","6820935910","6814916515","6814916516","1837212101","1837212103",
      "6813411589","216155217","6813411590","1472141024","6813405280","348121864",
      "348121996","6813405275","1732243544","6819179749","4015372463","4015372469",
      "1732243620","6814916523","6814916522","6813379547","6813379546","6813379536",
      "6813379545","6813379544","6813379495","6813379494","3398574883","6813565327",
      "3402810298","6813565328","3088548446"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path2) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt2) << "miles" << std::endl;
  EXPECT_EQ(path2, gt2);
  
  // Reverse the input from CVS Pharmacy to Chick-fil-A
  path2 = m.CalculateShortestPath_Dijkstra("CVS Pharmacy", "Chick-fil-A");
  std::reverse(gt2.begin(),gt2.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path2) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt2) << "miles" << std::endl;
  EXPECT_EQ(path2, gt2);

  // TEST3
  // Test from Startbucks to Starbucks
  auto path3 = m.CalculateShortestPath_Dijkstra("Starbucks", "Starbucks");
  std::vector<std::string> gt3{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path3) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt3) << "miles" << std::endl;
  EXPECT_EQ(path3, gt3);
  
  // Reverse the input from Startbucks to Starbucks
  path3 = m.CalculateShortestPath_Dijkstra("Starbucks", "Starbucks");
  std::reverse(gt3.begin(),gt3.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path3) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt3) << "miles" << std::endl;
  EXPECT_EQ(path3, gt3);
}

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapStudentTest, CalculateShortestPath_Bellman_Ford){
  TrojanMap m;
  // TEST1
  // Test from Ralphs to Target
  auto path1 = m.CalculateShortestPath_Bellman_Ford("Ralphs", "Target");
  std::vector<std::string> gt1{
      "2578244375","4380040154","4380040158","4380040167","6805802087","8410938469",
      "6813416131","7645318201","6813416130","6813416129","123318563","452688940",
      "6816193777","123408705","6816193774","452688933","452688931","123230412",
      "6816193770","6787470576","4015442011","6816193692","6816193693","6816193694",
      "4015377691","544693739","6816193696","6804883323","6807937309","6807937306",
      "6816193698","4015377690","4015377689","122814447","6813416159","6813405266",
      "4015372488","4015372487","6813405229","122719216","6813405232","4015372486",
      "7071032399","4015372485","6813379479","6813379584","6814769289","5237417650"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path1) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt1) << "miles" << std::endl;
  EXPECT_EQ(path1, gt1);
  
  // Reverse the input from Ralphs to Chick-fil-A
  path1 = m.CalculateShortestPath_Bellman_Ford("Target", "Ralphs");
  std::reverse(gt1.begin(),gt1.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path1) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt1) << "miles" << std::endl;
  EXPECT_EQ(path1, gt1);

  // TEST2
  // Test from Chick-fil-A to CVS Pharmacy
  auto path2 = m.CalculateShortestPath_Bellman_Ford("Chick-fil-A", "CVS Pharmacy");
  std::vector<std::string> gt2{
      "4547476733","6820935910","6814916515","6814916516","1837212101","1837212103",
      "6813411589","216155217","6813411590","1472141024","6813405280","348121864",
      "348121996","6813405275","1732243544","6819179749","4015372463","4015372469",
      "1732243620","6814916523","6814916522","6813379547","6813379546","6813379536",
      "6813379545","6813379544","6813379495","6813379494","3398574883","6813565327",
      "3402810298","6813565328","3088548446"}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path2) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt2) << "miles" << std::endl;
  EXPECT_EQ(path2, gt2);
  
  // Reverse the input from CVS Pharmacy to Chick-fil-A
  path2 = m.CalculateShortestPath_Bellman_Ford("CVS Pharmacy", "Chick-fil-A");
  std::reverse(gt2.begin(),gt2.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path2) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt2) << "miles" << std::endl;
  EXPECT_EQ(path2, gt2);

  // TEST3
  // Test from Startbucks to Starbucks
  auto path3 = m.CalculateShortestPath_Bellman_Ford("Starbucks", "Starbucks");
  std::vector<std::string> gt3{}; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path3) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt3) << "miles" << std::endl;
  EXPECT_EQ(path3, gt3);
  
  // Reverse the input from Startbucks to Starbucks
  path3 = m.CalculateShortestPath_Bellman_Ford("Starbucks", "Starbucks");
  std::reverse(gt3.begin(),gt3.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path3) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt3) << "miles" << std::endl;
  EXPECT_EQ(path3, gt3);
}

// Test CycleDetection function
TEST(TrojanMapStudentTest, CycleDetection) {
  TrojanMap m;
  // Test case 1 - With cycle
  std::vector<double> square1 = {-118.299, -118.290, 34.021, 34.011};
  auto sub1 = m.GetSubgraph(square1);
  bool result1 = m.CycleDetection(sub1, square1);
  EXPECT_EQ(result1, true);

  // Test case 2 - No cycle
  std::vector<double> square2 = {-118.299, -118.298, 34.021, 34.020};
  auto sub2 = m.GetSubgraph(square2);
  bool result2 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result2, false);

  // Test case 3 - Empty Subgraph
  std::vector<double> square3 = {-118.299, -118.299, 34.021, 34.021};
  auto sub3 = m.GetSubgraph(square2);
  bool result3 = m.CycleDetection(sub2, square2);
  EXPECT_EQ(result3, false);

}

// Test TSP Brute Force function
TEST(TrojanMapStudentTest, TSP_Brute_force) {
  TrojanMap m;
  
  // Test case 1 - 4 locations
  std::vector<std::string> input{"6805221419","8221360811","9591449435","7853031384"}; // Input location ids 
  auto result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6805221419","8221360811","9591449435","7853031384","6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);

  // Test case 2 - 0 locations
  input = {}; // Input location ids 
  result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second.size(), 0);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

  // Test case 3 - 1 locations
  input = {"6805221419"}; // Input location ids 
  result = m.TravellingTrojan_Brute_force(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {"6805221419", "6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second[result.second.size() - 1].size(), 2);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

}

// Test TSP Backtracking function
TEST(TrojanMapStudentTest, TSP_Backtracking) {
  TrojanMap m;
  
  // Test case 1 - 4 locations
  std::vector<std::string> input{"6805221419","8221360811","9591449435","7853031384"}; // Input location ids 
  auto result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6805221419","8221360811","9591449435","7853031384","6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);

  // Test case 2 - 0 locations
  input = {}; // Input location ids 
  result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second.size(), 0);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

  // Test case 3 - 1 locations
  input = {"6805221419"}; // Input location ids 
  result = m.TravellingTrojan_Backtracking(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {"6805221419", "6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second[result.second.size() - 1].size(), 2);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

}

// Test TSP 2-opt function
TEST(TrojanMapStudentTest, TSP_2opt) {
  TrojanMap m;
  
  // Test case 1 - 4 locations
  std::vector<std::string> input{"6805221419","8221360811","9591449435","7853031384"}; // Input location ids 
  auto result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"6805221419","8221360811","9591449435","7853031384","6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second[result.second.size() - 1].size(), input.size() + 1);

  // Test case 2 - 0 locations
  input = {}; // Input location ids 
  result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second.size(), 0);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

  // Test case 3 - 1 locations
  input = {"6805221419"}; // Input location ids 
  result = m.TravellingTrojan_2opt(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  gt = {"6805221419", "6805221419"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  EXPECT_EQ(result.second[result.second.size() - 1].size(), 2);
  EXPECT_EQ(m.CalculatePathLength(gt), 0);

}

// Test FindNearby function
TEST(TrojanMapStudentTest, FindNearbyTest) {
  TrojanMap m;
  
  // Standard input
  std::string attribute = "supermarket"; std::string location = "Target"; double radius = 1; int k = 10;
  auto result = m.FindNearby(attribute, location, radius, k);
  std::vector<std::string> gt{"Trader Joes", "Cal Mart Beer & Wine Food Store", "Ralphs"};
  for (auto &i : gt) {
    i = m.GetID(i);
  }
  EXPECT_THAT(result, UnorderedElementsAreArray(gt));

  // 0 radius, 0 locations
  gt = {};
  result = {};
  result = m.FindNearby(attribute, location, 0, 0);
  EXPECT_EQ(result.size(), 0);

}
