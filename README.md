# Searching-and-Sorting-Testped-Program
- This is a repository for Searching and Sorting Testped Program spesification.
- The source code was made for 5G00DM61-3003 Programming Languages 3.

## Concept
- In this project a menu driven test bed program for searching and / or sorting algorithms is made. The algorithms are from teaching sessions. The points you get from this project depends on how much work you do for it. The more functions you include in the program the more points you get. Don’t remove any working functionalities when you made a new function; all functions must work (already made and new ones) at any point of time.
- You get 0 – 5 points out of this project.
- We will use some time in the last teaching sessions to give support for this project. We will also combine making home exercises and this project in the end of this course. Basically you can utilize some code from home exercises in this project.
- Program features are divided into five groups; groups 1 and 2 involve searching algorithms and groups 3 – 5 involve sorting algorithms. If you make search functions do first function 1 and then function 2 (there are dependencies between these two parts). If you make sorting functions do them in the order 3, 4 and 5. There are no dependencies between searching and sorting parts of the project; you can do solely groups 1 and 2 and solely groups 3 – 5 or all of them.

## Requirements
### 1.1.	More details on the requirements of Group Number 1

In this alternative, the data to be searched is generated as shown on page 9 of the lecture slide tr7.pdf; the user only enters the data size here. For example, if 10 is entered as the data size, then the following data is generated: 1, 3, 5,…, 19. The data to be searched contains only integers both at this function and at other functions of the application of the search algorithms. Similarly, in sorting, we only sort integers.
As a result of the search, the program prints the success information of it and if the key value to be searched was found (= success) then in the list its location is also printed.
With regard to entering the key value to be searched, there are two possibilities: the user enters it directly; for example, 11, or the key value to be searched for is generated as a random number as described on page 9 in the slide set tr7.pdf. You can choose either way or if you are interested also doing both of them is ok.

### 1.2.	More details on the requirements of Group Number 2

In binary search, the data to be searched and the key value to be searched are generated in the same way as presented in previous section (1.1). Similarly, the presentation of the results is done as described in Chapter 1.1.
If the user selects the performance comparison function for this function group, the sequential search and binary search algorithms are run on the exact same data with the same search keys. During the search, the number of comparisons as well as the elapsed wall clock time are observed; these are both printed for both search algorithms. In the performance comparison, both the data to be searched and the key to be searched are randomly generated following the instructions on page 9 of the tr7.pdf slide series.
In order for the results of the performance comparison to be more reliable, both search algorithms must be called many times (e.g. 10 times) with different search keys during the test run in order to make the results more reliable. Otherwise, for example in a binary search, the value found in the middle of the data may be generated as a random key, and the search ends immediately and the results are distorted. The user can also enter the number of repetitions.
In addition, a performance comparison is even more reliable if about half of the search ends in success and half does not. When we generate a search key at random this requirement is met enough. Look more instructions on slideset tr7.pdf!
Below is a suggestion for output of a performance run - here all the search algorithm variants that have been covered in the lessons have been run through; all you have to do is to run only sequence search and some binary search variant; not all binary search variants:
 

### 1.3.	More on the requirements of Group Number 3

Here, user enters the size of the data to be sorted with insertion sort; for example, input 1000 here means that the program generates 1000 random integer values in some table that will be sorted. In the example situation, the limits for generating each random number could be from 0 to 10,000, so that the generation of the same numbers in the data would be reasonably rare. Thus, the possible value range of each individual number to be generated is ten times the number of numbers to be generated.
The program prints out some small number of items in the beginning of a table to be sorted before sorting; e.g., 200 numbers from the beginning, and the same area of the table is printed after sorting to ensure that the algorithm works correctly for at least this slice area. The size of the area is asked from the user; if desired, the entire material is also printed before and after sorting, thus ensuring the success of the entire sorting.
### 1.4.	More details on the requirements of Group Number 4

For inputs and outputs, the same requirements apply here as in section 1.3. for the new implemented sorting algorithm.

## Manual
This project using meson to build, so you have to download and install it to your computer.
[Meson Build](https://mesonbuild.com/)

### Build
``` cli
meson build //  Initialize the build
cd build // Move to build dirrectory
ninja && ./main // Run built
///Fast build and run
meson build && ninja -C build && ./build/main
```


### Change name of built
Change this code in meson.build for changing the name.
```
// meson.build
...
executable('main', './/src//main.cpp', link_with : lib) // change main to another name
...
```
## Issues
