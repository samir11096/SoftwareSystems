//Question->Create a hard link using link system call
//Name -> Samir Ahmed Ghouri Roll-> MT2022100
#include<unistd.h>
#include<stdio.h>
int main()
{
	// will create a hardlink hlink with same inode in the previous directory
	if(link("source" , "../hlink")<0){
		perror("Hard Link:");
	}
	return 0;
}
