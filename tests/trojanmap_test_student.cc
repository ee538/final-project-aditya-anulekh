#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"


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