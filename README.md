# Shell-implementation
UNIX Shell and Program Selection Feature

Design and implemented a process model and OS utility, i.e., Shell.

Description of the project:

1) This project consists of a program to serve as a shell interface that accepts user commands and then executes each command in a separate process.

2) Also the shell interface provides a program selection featyre that allows user to access the available executable programs from the current directory. The user will be able to access all executable programs.

Implementation of the project:

The c++ program accepts the user commands and executes the command by creating a child process after parsing the inputs into tokens. If the command had "&" it will for the child process to finish. 

Selection program is implemented by doing the following one by one:
1.	getExecutableFiles: This function gets the executable files in the current directory by running the "find . -type f -executable" command using popen() call. The popen() function opens a process by creating a pipe, forking, and invoking the shell. The resulting stream is then used for reading from the pipe. fgets is command for the same. Since fgets terminates on a new line character, we can use this store each executable file in a array called 'files'. 
2.	printUserInput: This function reads each file from the above array 'files' and prints a number associated with each. 
3.	getUserInput: This function gets the user input for which file to execute. 
4.	executeUserInput: This function executes the user input file by using the same function 'createProcess' that I had for Assignment Part A. The createProcess then forks a child process and waits for it to complete



