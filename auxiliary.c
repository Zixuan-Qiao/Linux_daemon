#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/param.h>
#include<sys/stat.h>

#define FILE_PATH "/home/user/timelop.txt"
#define EXEC_PATH "/home/user/git/daemon/testd"

int getFileSize() // obtain file size to determine if daemon is running
{
	int size;
	FILE *fp=fopen(FILE_PATH, "r");
	if(!fp)
		return -1;	
	fseek(fp,0L,SEEK_END);
	size=ftell(fp);
	fclose(fp);
	return size;
}

void main()
{
	int pid;
	pid=fork();
	if(pid<0){ // error
		exit(1);
	}
	else if(pid>0){ // success
		exit(0); //parent exits
	}
	setsid(); // set the process as session leader

	for(int i=0;i<NOFILE;i++){ // close inherited files
		close(i);
	}
	chdir("/"); // change directory
	umask(0); // set permission
	int size1; 
	int size2; 
	size1=getFileSize();
	while(1){
		sleep(5);
		size2=getFileSize();
		if(size2>size1) // daemon is running
			size1=size2;
		else // daemon is terminated
			system(EXEC_PATH); // re-start daemon
	}

}

