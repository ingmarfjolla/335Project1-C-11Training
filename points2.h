/*******
TITLE: Points2.h
NAME : INGMAR FJOLLA
We created a class that contains a template object used to store a sequence of 2D points as described
by Professor Raja 

********/
#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>
using namespace std;

namespace teaching_project {
/*The class Points2, as described by professor Raja 
was that the purpose of this assignment is to have you create a Points2 class 
from scratch with limited help from the STL. Points 2 desribes a sequence of 
of 2D points such as : Example 1: (1, 3), (4, 5) and 
Example 2: (1.2, 3.4), (5.6, 10.1), (11.1, 12.0). First example being filled with int types
and the second having double coordinates.
*/
template<typename Object>
class Points2 {
 
 public:
  // Default "big five" -- you have to alter them for your assignment.
  // That means that you will remove the "= default" statement.
  //  and you will provide an implementation.

  // Zero-parameter constructor. 
  // Set size to 0.
  //also set sequence to a nullptr
  Points2(): size_(0),sequence_(nullptr)
  {}

  // Copy-constructor.
  Points2(const Points2 &rhs)   //: size_{rhs.size_}
  {
    //if rhs.size is zero (size is empty) then set privae memebrs to zero
    if(rhs.size()==0)
    {
      
      size_ = 0;
      sequence_ = nullptr;

    }
    else{
      size_ = rhs.size_;
      //dynamically allocate memory to create space for the sequence
      sequence_ = new array<Object, 2>[size_];
      copy(rhs.sequence_, rhs.sequence_+rhs.size_, sequence_);
    }
  }

  // Copy-assignment. If you have already written
  // the copy-constructor and the move-constructor
  // you can just use:
  // {
  // Points2 copy = rhs; 
  // std::swap(*this, copy);
  // return *this;
  // }
  //given code
  Points2& operator=(const Points2 &rhs)  
  {
    Points2 copy = rhs; 
    swap(*this, copy);
    return *this;
  }

  // Move-constructor. 
  //transfers everything from rhs to new object
  //then deletes whatever is in rhs
  Points2(Points2 &&rhs)  
  {
    sequence_=move(rhs.sequence_);
    size_= move(rhs.size_);
    rhs.sequence_ = nullptr;
    rhs.size_ = 0;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs)  
  {
      if(this == &rhs)
      {
        return *this;
      }
      swap(size_, rhs.size_);
      swap(sequence_, rhs.sequence_);
      return *this;

  }
  //destructor responsible for reallocating space
  ~Points2()
  {
  
    delete[] sequence_;
    sequence_=nullptr;
    //size_ = 0;
  }

  // End of big-five.

  // One parameter constructor.
  Points2(const std::array<Object, 2>& item): sequence_(new array<Object, 2>{item}), size_(item.size())
  {}

  // Read a chain from standard input.
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;
    // Allocate space for sequence.
    size_ = size_of_sequence;
    sequence_ = new array<Object, 2>[size_];
    
    Object token;
    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.
      sequence_[i][0] = token;
      input_stream >> token;
      sequence_[i][1] = token;
    }
    
  }

  size_t size() const {
  
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 
     //bounds checking
    if(location <= -1 || location > size_-1)
    {
      cout << "Location out-of-range" << endl;
      abort();
    }
    else
    {
      return sequence_[location];
    }
  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2 operator+(const Points2 &c1, const Points2 &c2) 
{
    //object to return
    Points2<Object> resulting_sequence;

    //compare sizes prior to beginning the loop, less if else statements
    if(c1.size_>c2.size_)
    {
      resulting_sequence.size_ = c1.size_;
    }
    else
    {
      resulting_sequence.size_ = c2.size_;
    }

    resulting_sequence.sequence_ = new array<Object, 2>[resulting_sequence.size_];
    for ( auto i =0 ; i < resulting_sequence.size_ ; i++)
    {
      if(c1.size_>c2.size_ && i >= c1.size_)
      {
        resulting_sequence.sequence_[i][0] = c1.sequence_[i][0];
        resulting_sequence.sequence_[i][1] = c1.sequence_[i][1];  
      }
      else if(c2.size_>c1.size_ && i >= c2.size_)
      {
        resulting_sequence.sequence_[i][0] = c2.sequence_[i][0];
        resulting_sequence.sequence_[i][1] = c2.sequence_[i][1];  
      }
      else{
        resulting_sequence.sequence_[i][0]=c1.sequence_[i][0] + c2.sequence_[i][0];
        resulting_sequence.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
      }
    }
    return resulting_sequence;

 }

 // Overloading the << operator.
 friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) 
{
   //makes sure its not empty 
  if(some_points2.size_ >=1)
  {
    for (size_t i = 0; i < some_points2.size_; i++)
    {
      out << "(" << some_points2.sequence_[i][0] << ", " << some_points2.sequence_[i][1] << ")" << " ";
    }
  }
  else
  {
    out << "()";
  }


  // if(some_points2.sequence_==nullptr || some_points2.size_<1)
  // {
  //   out<<"()"; //the case of the empty 
  // }

  // else{

  //   for(size_t i = 0;i< some_points2.size_;i++)
  //   {
  //     out<<"("<< some_points2.sequence_[i][0]<<", "<<some_points2.sequence_[i][1]<<")";
  //   }

  //   out << endl;
  //   return out;
  // }
  out << endl;
  return out;


 }

 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
