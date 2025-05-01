/*    @file MyHash.cpp   
      @author < Allyssa Dalton >
      @date < March 16th, 2025 >

			@description Implements a hash table class (unordered multiset)
*/

#include <string>
#include <iostream>

#include "MyHash.h"

# define RESIZE_LIMIT 0.7

MyHash::MyHash(bool resize, unsigned start_size, Collision_t method):n(0),method(method), resize(resize){
  data = new Bucket[start_size]; //creates bucket array of size start_size
  max_size = start_size;
};   

MyHash::MyHash(MyHash &other){
  method = other.method;
  resize = other.resize;
  max_size = other.max_size;
  //these two lines create memory leak
  //data = other.data;
  //n = other.n;
  data = new Bucket[max_size];
  n = 0;
  for(unsigned i = 0; i < max_size; i++){
    if (other.data[i].used){ // other [i]
      insert(other.data[i].value);
    }
  }
}

MyHash& MyHash::operator=(const MyHash& other){
  method = other.method;
  resize = other.resize;
  max_size = other.max_size;
  delete[] data;
  data = new Bucket[max_size];
  n = 0;
  for(unsigned i = 0; i < max_size; i++){
    if (other.data[i].used){ // other [i]
      insert(other.data[i].value);
    }
  }
  return *this;
}

MyHash::~MyHash(){
  delete[] data;
}

void MyHash::print(){
  cout << "Stored " << n << " values: ";
  for(unsigned i = 0; i < max_size; i++){
    if(data[i].used){
      cout << data[i].value << ", ";
    }
  }
  cout << endl;
}

unsigned int MyHash::hashSlingingSlasher(unsigned int i, int value){ //hashing function
  unsigned int stepper;
  if (method == double_hash){
    stepper = 1 + (value % (max_size - 2)); 
    if (stepper == 0){stepper = 1;}
  }
  else{stepper = 1;}
  return stepper;
}

void MyHash::insert(int value){ 
  if (resize && (float(n) / max_size > RESIZE_LIMIT)){resizer();} // Resize if load factor exceeds 0.7 and if resize is true 
  unsigned int i = value % max_size; //finds the location to store it
  unsigned int stepper = hashSlingingSlasher(i, value);
  /*
  unsigned int stepper;
  if (method == double_hash){
    stepper = 1 + (value % (max_size - 2)); 
    if (stepper == 0){stepper = 1;}
  }
  else{stepper = 1;}
*/
   
  for (unsigned int tried = 0; tried < max_size; tried++){ //goes the the entire list starting a i and ends at i - 1 
    if(!data[i].used || (data[i].used && data[i].deleted)){ //checks if location has been used before it's used
      data[i].used = true; //signifies that the location has been used
      data[i].value = value; //gives location i the value being inserted
      data[i].deleted = false;
      n++; 
      return;
    }
    i = (i + stepper) % max_size;
  }
}

bool MyHash::contains(int value){ 
  unsigned int i = value % max_size; //finds the location to store it
  unsigned int stepper = hashSlingingSlasher(i, value);
  /*
  unsigned int stepper;
  if (method == double_hash){
    stepper = 1 + (value % (max_size - 2)); 
    if (stepper == 0){stepper = 1;}
  }
  else{stepper = 1;}
  */

  for (unsigned int tried = 0; tried < max_size; tried++){
    //checks if location is used and has the search value
    if (!data[i].used) { 
      if (!data[i].deleted){return false;} // Stop if slot has NEVER been used
    }
    if(!data[i].deleted && data[i].used && data[i].value == value){return true;}
    i = (i + stepper) % max_size;
    /*else if returns false if location i hasn't be used AND it's value hasn't been deleted, meaning that since value 
    isn't there and no value has ever been there, it would've tried to have placed the value being searched for there first.
    Since it's not there, value isn't in the array*/
    //else if (!data[i].used && !data[i].deleted){return false;}
    //else{i = (i + stepper) % max_size;}
    //else if (!data[i].used && !data[i].deleted){return false;}
    //i = (i + stepper) % max_size;
  }
  return false;
}

unsigned MyHash::count(int value){
  int counter = 0;
  if(!contains(value)){return counter;}
  unsigned int i = value % max_size; //finds the location to store it
  unsigned int stepper = hashSlingingSlasher(i, value);
  /*unsigned int stepper;
  if (method == double_hash){
    stepper = 1 + (value % (max_size - 2)); 
    if (stepper == 0){stepper = 1;}
  }
  else{stepper = 1;}
  */
  
  // checks through the entire table
  for (unsigned int tried = 0; tried < max_size; tried++){
    if (data[i].used && !data[i].deleted && data[i].value == value){counter++;}  // increases counter by one if value exist in spot
    else if (!data[i].used && !data[i].deleted){return counter;} //ends for loop if theres an empty location 
    i = (i + stepper) % max_size; // % max_size prevents it going out of bounds
  }
  return counter;
}

void MyHash::erase(int value){
  unsigned int i = value % max_size; //finds the location to store it
  unsigned int stepper = hashSlingingSlasher(i, value);
  /*
  if (method == double_hash){
    stepper = 1 + (value % (max_size - 2)); 
    if (stepper == 0){stepper = 1;}
  }
  else{stepper = 1;}
  */
  for (unsigned int tried = 0; tried < max_size; tried++){
    if (!data[i].deleted && data[i].used && data[i].value == value){ //checks if location is used and has the search value
      data[i].deleted = true;
      n--;
      return;
    }
    i = (i + stepper) % max_size; //using % max_size prevents it going out of bounds
  }
  return;
}

unsigned MyHash::size(){
  int counter = 0; 
  for (unsigned int i = 0; i < max_size; i++){
    if (data[i].used && !data[i].deleted){counter++;} //increases counter if i has been used 
  }
  return counter;
}

unsigned MyHash::capacity(){
  return max_size; //capacity is the max size
}

void MyHash::resizer(){
  unsigned int ogSize = max_size;
  max_size *= 2; //new possible size is twice old possible size
  Bucket* ogData = data;
  data = new Bucket[max_size];
  for (unsigned int i = 0; i < ogSize; i++){
    if (ogData[i].used && !ogData[i].deleted){
      insert(ogData[i].value);
    }
  }
  delete[] ogData;
}

unsigned int MyHash::countContainsProbes(int value) {
  unsigned int probes = 0;
  unsigned int i = value % max_size; 
  unsigned int stepper = hashSlingingSlasher(i, value);
  /*
  unsigned int stepper;
  if (method == double_hash){
      stepper = 1 + (value % (max_size - 2));
      if (stepper == 0){stepper = 1;}
  } 
  else{stepper = 1;}
  */
  for (unsigned int tried = 0; tried < max_size; tried++) {
      probes++;
      if (!data[i].deleted && data[i].used && data[i].value == value){return probes;}
      if (!data[i].used){return probes;}
      i = (i + stepper) % max_size;
  }
  return probes;
}
