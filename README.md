# Programming Task 3 |  Interior-Point Algorithm
**Introduction to Optimization - Fall 2024**

## Team
- **Elina Kuzmicheva**  
- **Maxim Fomin**   
- **Sergei Melnikov**   

## Programming Language
- **C++**

## Input Format
The input contains:
- A vector of coefficients of supply  `S`
- A vector of coefficients of demand `D`
- A matrix of coefficients of costs `C`

## Tests Statements
###Test 1: Not Balanced Problem
```
-- Input --
10 20 30
10 10 10
1 2 3
4 5 6
7 8 9
-- Output --
The problem is not balanced:(
```
###Test 2: Not applicable input for this methods (all 0)
```
-- Input --
10 20 30
30 20 10
0 0 0
0 0 0
0 0 0
-- Output --
The method is not applicable:(
```
###Test 3: Not applicable input for this methods (negative values)
```
-- Input --
10 20 30
30 20 10
-1 -2 -3
-4 -5 -6
7 8 9
-- Output --
The method is not applicable:(
```
###Test 4: Correct input
```
-- Input --
160 140 170
120 50 190 110
7 8 1 2
4 5 9 8
9 2 3 6
-- Output --
Transportation problem:
r1 7 8 1 2 160
r2 4 5 9 8 140
r3 9 2 3 6 170
Demand 120 50 190 110 470
Russell’s approximation method:
r1 0 0 160 0 160
r2 120 0 0 20 140
r3 0 50 30 90 170
Demand 120 50 190 110 470
Total cost:1530
Vogel’s approximation method:
r1 0 0 50 110 160
r2 120 20 0 0 140
r3 0 30 140 0 170
Demand 120 50 190 110 470
Total cost:1330
North-West corner method:
r1 120 40 0 0 160
r2 0 10 130 0 140
r3 0 0 60 110 170
Demand 120 50 190 110 470
Total cost:3220
```
