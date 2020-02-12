#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <errno.h>
#include "acl.h"

int main(int argc, char  *argv[])
{
    char buff[1];
    char* input = (char*)malloc(sizeof(char));
    int size = 0;
    while (read(0,buff,1)>0)
    {
        if(buff[0]-'\n'==0){
            break;
        }
        input[size] = buff[0];   
        size+=1;
        input = (char*)realloc(input,(size+1)*sizeof(char));
    }
    input[size] = '\0';


    printf("%s\n",input);


    return 0;
}
