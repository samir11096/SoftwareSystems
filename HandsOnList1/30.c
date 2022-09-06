#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
int init_daemon(void){
	if(!fork()){
		setsid();
		chdir("/");
		umask(0);

		if(execl("/usr/bin/sh","sh","/home/samir/Desktop/Sem1/Software System/HandsOnList1/script.sh",(char*)NULL)<0){
			perror("program");
		}
		return 0;
	}
	else{
		exit(0);
	}
}

int main(){
	init_daemon();
	return 0;
}
