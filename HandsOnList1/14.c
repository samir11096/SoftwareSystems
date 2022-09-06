// write comments for revision purpose
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <time.h>
       #include <stdio.h>

       int main(int argc, char *argv[])
       {
           struct stat sb;

           if (lstat(argv[1], &sb) == -1) {
               perror("lstat");
           }


           printf("File type:                ");
//((mode & S_IFMT) ==filetypecode)
//Macro: int S_IFMT
//This is a bit mask used to extract the file type code from a mode value.
//
//These are the symbolic names for the different file type codes:
//
//S_IFDIR
//This is the file type constant of a directory file.
//
//S_IFCHR
//This is the file type constant of a character-oriented device file.
//
//S_IFBLK
//This is the file type constant of a block-oriented device file.
//
//S_IFREG
//This is the file type constant of a regular file.
//
//S_IFLNK
//This is the file type constant of a symbolic link.
//
//S_IFSOCK
//This is the file type constant of a socket.
//
//S_IFIFO
//This is the file type constant of a FIFO or pipe.
	switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

	return 0;
       }
