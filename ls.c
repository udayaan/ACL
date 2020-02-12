#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>

int main(int argc, char  *argv[])
{
    struct dirent *de;  // Pointer for directory entry 
  
    DIR *dr = opendir(argv[1]); 
  
    if (dr == NULL)   
    { 
        printf("Could not open current directory" ); 
        exit(EXIT_FAILURE); 
    } 
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
    // for readdir() 
    while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    
    closedir(dr);  
    
    exit(EXIT_SUCCESS);
}
