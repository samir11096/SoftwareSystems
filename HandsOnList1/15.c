#include<stdio.h>
int main(){
		extern char **environ; // environ points to an array of pointers to string.
		int i = 0 ;
		while(environ[i]){
			printf("%s\n",environ[i++]);
		}
		return 0;
}




