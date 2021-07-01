// What not to do !

#include <iostream>
#include <vector>

#define SIZE 5000

// 1. Never return refernce to stack allocated objects like this.
template <typename T> T *vector_to_array(std::vector<T> vec) {
  // from vector to fixed size array
  // return the array back.
  // array in stack memory (activation record of this call.)
  T arr[vec.size()];
  std::copy(vec.begin(), vec.end(), arr);
  std::cout << arr[1580] << "\n";
  return arr;
}

// 2. This is expensive since we return the whole vector
// Does copy-elision work here?
template <typename T> std::vector<T> push_back_to_vector(std::vector<T> vec) {
  vec.push_back(25412123);
  return vec;
}

int main(void) {
  std::vector<long long int> intVec;

  // Create a large vector.
  for (auto i = 0; i < SIZE; i++) {
    intVec.push_back(i << 2);
  }

  // Try converting that into an array in a naive way.
  long long int *arr = vector_to_array<long long int>(intVec);

  // Access elements in the converted array.
  std::cout << arr[1580] << "\n";

  intVec = push_back_to_vector(intVec);

  std::cout << intVec.back() << "\n";
  return 0;
}

// The compiler warned us. 
/*
example.cpp: In instantiation of ‘T* vector_to_array(std::vector<T>) [with T = long long int]’:
example.cpp:30:61:   required from here
example.cpp:13:10: warning: address of local variable ‘arr’ returned [-Wreturn-local-addr]
   13 |   return arr;
      |          ^~~
example.cpp:10:5: note: declared here
   10 |   T arr[vec.size()];
      |     ^~~
*/

// Running this example.
/*
6320
AddressSanitizer:DEADLYSIGNAL
=================================================================
==38186==ERROR: AddressSanitizer: SEGV on unknown address 0x000000003160 (pc 0x563dedc53728 bp 0x7ffdc1cef110 sp 0x7ffdc1ceef70 T0)
==38186==The signal is caused by a READ memory access.
    #0 0x563dedc53727 in main /home/zcluster55/Documents/Research/PSE-Program-Examples/baseline-exp/src/example.cpp:33
    #1 0x7f71f78240b2 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x270b2)
    #2 0x563dedc5342d in _start (/home/zcluster55/Documents/Research/PSE-Program-Examples/baseline-exp/src/example.out+0x242d)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/zcluster55/Documents/Research/PSE-Program-Examples/baseline-exp/src/example.cpp:33 in main
==38186==ABORTING
*/
