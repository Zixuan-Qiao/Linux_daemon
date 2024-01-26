#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/param.h>
#include<sys/stat.h>
#include<time.h>

#define FILE_PATH "/home/user/timelog.txt"

void main()
{
	int pid;
	pid=fork();
	if(pid<0) // error
	{
		exit(1); 
	}
	else if(pid>0)// success
	{
		exit(0);// parent exit
	}
	setsid(); // set the process as session leader

	for(int i=0;i<NOFILE;i++){// close inherited files
		close(i);
	}
	chdir("/"); // change work directory
	umask(0); // set access permission
	FILE *fp;
	fp=fopen(FILE_PATH,"a");
	if(fp>0){ // success
		fprintf(fp,"start:"); // print “start：” at the beginning
	}
	fclose(fp);
	while(1){ // record system timestamp every 5 seconds
		time_t current = time(NULL);
		struct tm *t = localtime(&current);
		fp=fopen(FILE_PATH,"a");
		if(fp>0){
			fprintf(fp,"%02d:%02d:%02d %04d-%02d-%02d\n", t->tm_hour, t->tm_min, t->tm_sec, t->tm_year+1900, t->tm_mon+1, t->tm_mday);
		}
		fclose(fp);
		sleep(5);
	}
}

