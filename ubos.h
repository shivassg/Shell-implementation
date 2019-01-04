#ifndef UBOS_H
#define UBOS_H

#include<iostream>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>

#define MAX_LINE 80 /*80 chars per line, per command*/

class ubos{

	private:
		char* args[MAX_LINE/2 + 1];
		char* point;
		int should_run;
		pid_t p_id;
		char input[1000];
		int count;

	public:
		int parsing(char input[],bool* shouldWait);
		void run();
		void createProcess(int i,bool shouldWait);
		void getExecutableFiles(char **files,int &numberOfFiles);
		void printUserInput(char **files,int numberOfFiles);
		int getUserInput();
		void executeUserInput(char **files, int number);
};

#endif
