#include "ubos.h"

using namespace std;

int ubos::parsing(char input[],bool* shouldWait){

	int i=0;
	point= strtok(input," ");
	while(point !=NULL && strlen(point)>0)
	{
		if(strcmp(point,"&")!=0){
		
		args[i++]=point;
		}else{
			*shouldWait=true;
		}
		point= strtok(NULL, " ");
		

	}
	args[i]=NULL;
	return i;
}


void ubos::getExecutableFiles(char **files, int &numberOfFiles) {
	FILE *in;
	char buffer[1024];	 
        int i = 0;
	in=popen("find . -type f -executable","r");
	while (fgets(buffer,sizeof(buffer),in) != NULL) {
		buffer[strcspn(buffer, "\n")] = 0;
                files[i] = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
                strcpy(files[i], buffer);
		//std::cout<<files[i];
                i++;
        }
        numberOfFiles = i;
	pclose(in);
}

void ubos::printUserInput(char **files, int numberOfFiles) {
 for(int i=0;i<numberOfFiles;i++){
	std::cout<<i+1<<"."<<"    "<<files[i]<<std::endl;
 }

}

int ubos::getUserInput() {
//User enters an input number.
        std::string number;
	std::cin>>number;
        if (number == "exit") {
           return -1;
        } else {
           return std::stoi(number, nullptr);
        }
}

void ubos::executeUserInput(char **files, int number) {
	//Execute the command which user gave. 
	//Create a child process execvp will run the command (File name).
	args[0]=files[number-1];
	args[1]=NULL;
	createProcess(1,true);
}

void ubos::run(){
	should_run=1;
	while(should_run){
		bool shouldWait=false;
		std::cout<<"UBOS> ";
		fflush(stdout);
		std::cin.getline(input,1000);
		//Need to check if user has given any input
		//Input can be exit or command or no input
		if(strcmp(input,"exit")==0){
			should_run=0;
			break;
		} else if(strcmp(input,"selection")==0){
			 //Displays the list of executeable files in the directory and gets user input
			char* files[100];
			int numberOfFiles=0;
			getExecutableFiles(files,numberOfFiles);
                        if (numberOfFiles > 0) {
				printUserInput(files,numberOfFiles);
				std::cout<<"UBOS> ";
				fflush(stdout);
				int userInputNumber = getUserInput();
				if (userInputNumber == -1) {
					should_run=0;
					break;
				}
				executeUserInput(files,userInputNumber);
				for (int i=0; i < numberOfFiles; i++) {
					free(files[i]);
				}
                        } else {
				std::cout<<"No Executable Found In Directory";
                        }
			
		} else{
			count=parsing(input,&shouldWait);
			createProcess(count,shouldWait);
		}
	}
}

void ubos::createProcess(int i,bool shouldWait){

	p_id = fork();
	if(p_id<0){
		cout<<"Process creation is failed";
		exit(1);
	}else if(p_id>0){
		if(shouldWait){
			waitpid(p_id,NULL,0);
		}
	}else if(p_id==0){
		if(execvp(args[0],args)==-1){
			cout<<"command not found";
			exit(1);
		}
	}
}
