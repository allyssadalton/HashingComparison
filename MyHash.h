#ifndef MYHASH_H
#define MYHASH_H  

/*    @file MyHash.h   
      @author < Allyssa Dalton >
      @date < March 16th, 2025 >

			@description Implements a class for implementing a hash table.
*/

#include <string>


using namespace std;

class Bucket{
  friend class MyHash; //Bucket friend of MyHash class, MyHash class can access private variables in Bucket
  public:
  Bucket():value(0), used(false), deleted(false){};

  private:
  int value;
  bool used;
  bool deleted;
};

// enumerated type
enum  Collision_t {
  linear,
  double_hash
};


class MyHash{
  public:
  MyHash(bool resize = true, unsigned start_size = 17, Collision_t method = linear);   // Default to auto-resizing, size 17, and linear probing
  MyHash(MyHash &other);        // Copy constructor
  MyHash& operator=(const MyHash& other); // Assignment operator
  ~MyHash();  // Destructor
  unsigned int countContainsProbes(int value);

  void resizer(); // resizes the hash table

  void print(); // Prints all stored values in any order.
  void insert(int value); // Insert value into the hash table.  
  bool contains(int value); // Returns true if value is in the hash table, false otherwise.

  void erase(int value); // Remove value from the hash table.  Does nothing if it doesn't exist.
                          // If multiple exist, only remove one.

  unsigned count(int value); // Return the number of times value is stored

  unsigned size();        // Returns the number of elements stored in the table
  unsigned capacity();    // Size of the array currently

  // Change me!
  unsigned int hashSlingingSlasher(unsigned i, int value);
  
  private:
  
  Bucket* data;           // Pointer to the array for the hash table

  unsigned n;             // Number of elements in the hash table
  unsigned max_size;      // Current capacity
  Collision_t method;     // Desired method
  bool resize;            // If resizing is allowed

  // Change or add anything you need in this file.

};


  
#endif