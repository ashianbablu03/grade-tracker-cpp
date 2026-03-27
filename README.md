# Student Grade Tracker (C++)

A command-line application that manages student course records and calculates cumulative GPA on a 4.0 scale.

## Features
- Add and remove courses with grades and credit hours
- Automatically converts numeric grades to letter grades (A/B/C/D/F)
- Calculates weighted cumulative GPA
- Saves and loads student records to/from a text file
- Formatted grade report display

## Concepts Demonstrated
- Object-Oriented Programming (Classes, Encapsulation)
- File I/O (ofstream / ifstream)
- STL Vectors
- Input validation

## How to Run
```bash
g++ grade_tracker.cpp -o grade_tracker
./grade_tracker
```

## Example Output
```
========================================
  Grade Report for: Ashian Bablu
========================================
Course                Grade     Letter  Credits
----------------------------------------
Calculus I            92.0      A       3
CS1 - C++ Prog        88.5      B       3
----------------------------------------
  Cumulative GPA: 3.50 / 4.00
========================================
```

## Technologies
- Language: C++
- Compiler: g++ (C++17)
