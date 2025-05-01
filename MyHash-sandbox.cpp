/*    @file sandbox.cpp    
      @author < Allyssa Dalton >
      @date < March 16th, 2025 >

			@description Sandbox for MyComplex
*/

#include <iostream>
#include <vector>
#include <cstdlib>


#include "MyHash.h"

using namespace std;

void testConflictPolicies(Collision_t method) {
  unsigned int tableSize = 10000; // Fixed table size
  MyHash hashTable(true, tableSize, method); // Disable resizing
  vector<int> values; // Store inserted values for testing

  // Test at different load factors
  for (float loadFactor = 0.1; loadFactor <= 1; loadFactor += 0.1){
      unsigned int numInserted = tableSize * loadFactor;
      values.clear();
      for (unsigned int i = 0; i < numInserted; i++){
          int randomnum = rand();
          hashTable.insert(randomnum);
          values.push_back(randomnum);
      }

      //counts probes
      //deepseek helped me out here
      unsigned int totalProbes = 0;
      for (int val : values){totalProbes += hashTable.countContainsProbes(val);} 

      double averageProbes = double(totalProbes) / numInserted;
      cout << "Load: " << loadFactor << " Hashes: " << averageProbes << endl;
  }
}
int main(int argc, char* argv[]) {
  cout << "Linear probing:" << endl;
  testConflictPolicies(linear);

  cout << "Double hashing:" << endl;
  testConflictPolicies(double_hash);

  return 0;
}
