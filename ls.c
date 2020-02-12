#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <errno.h>
#include "acl.h"
#include<dirent.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char  *argv[])
{
    struct dirent *de; 
  
    DIR *dr = opendir(argv[1]); 
  
    if (dr == NULL)   
    { 
        printf("Could not open current directory" ); 
        exit(EXIT_FAILURE); 
    } 

    while ((de = readdir(dr)) != NULL) {
        if(strcmp(de->d_name,"..")!=0 && strcmp(de->d_name,".")!=0) {
            struct stat filestat;

            if(stat(de->d_name,&filestat)!=0) {
                printf("%s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }

            int size = filestat.st_size;
            struct passwd* user; 
            if((user=getpwuid(filestat.st_uid))==NULL){
                exit(EXIT_FAILURE);
            }
            
            struct group* grp; 
            if((grp=getgrgid(filestat.st_gid))==NULL){
                exit(EXIT_FAILURE);
            }
            printf("owner:%s  group:%s %d   %s   %s \n", user->pw_name, grp->gr_name, size, de->d_name, 
            S_ISDIR(filestat.st_mode)?"directory":"file"); 
        }
    }

    closedir(dr);  
    
    exit(EXIT_SUCCESS);
}
