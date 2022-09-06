#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd = open("example.txt" , O_RDONLY);

	if(fd<0){
		perror("program");
	}

	struct stat fst ; 

	int ret = fstat(fd , &fst);

	if(ret<0)
	{
		perror("stat");
	}

	int inode_number = fst.st_ino;
	int hard_links = fst.st_nlink;
	int uid = fst.st_uid;
	int gid = fst.st_gid;
	int sz = fst.st_size;
	int block_size = fst.st_blksize;
	int n_block = fst.st_blocks;
	int last_access = fst.st_atime;
	int last_mod = fst.st_mtime;
	int chg_time = fst.st_ctime;

	printf("Inode number of the given file is %d\n", inode_number);
	printf("Last time of access is %d\n" , last_access);
	printf("Last modified time is %d\n" , last_mod);
	printf("Number of hard links is %d\n" , hard_links);
	
	return 0;
}




