# CS210-projects
projects from CS-210 Programming Languages

In this project the 'client' is a grocery store looking to access and analyze daily sales. The sales data is input as a file and the program provides the user with the ability to consolidate/print the data, search for a particular item within the data, and print a histogram of the data. C++ handles the main method while calling a number of functions in Python to work with the files.

This is the first project where I have integrated C++ and Python. The wrappers used in C++ to call Python functions I think are the trickiest/most challenging bit to understand. On the other hand, using them and moving between C++ and Python is fairly straightforward. The ability to integrate languages like this is a powerful tool/skill to use in other project going forward. The code could be enhanced in the future by using a Python library to create a visual for the histogram function as opposed to passing a file back to C++. It can also be enhanced/made more maintainable by writing functions that take care of the various sub-menu display outputs as opposed to stuffing that formatting in with the functions that call Python. 
