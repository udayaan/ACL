#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/xattr.h>
#include<errno.h>
#include"./acl.h"

int main(int argc, char  *argv[])
{
    char* path = "./testfile";
    char* name = "user.test";
    char* value = "testtest";
    char buf[0];
    if(setxattr(path,name,value,8,0)!=0) {
        printf("1 %s\n",strerror(errno));
        exit(1);
    }
    int size =  getxattr(path,name,&buf,0);
    printf("%d\n",size);
    char buf2[size+1];
    getxattr(path,name,&buf2,size);
    buf2[size] = '\0';
    printf("%s\n",buf2);

    // struct acl* meta = (struct acl*)malloc(sizeof(struct  acl));
    // meta->acl = argv;
    // meta->acllen = argc;
    // char** ag = meta->acl;
    // for (int i=0;i<argc;++i) {
    //     printf("%s\n",ag[i]);
    // }
    // printf("%li\n",strlen(ag[0]));

    // char* aclbuf = (char*)malloc(strlen(ag[0])*sizeof(char));
    // memcpy(aclbuf,ag[0],strlen(ag[0])*sizeof(char));
    
    // for (int i=0;i<strlen(ag[0]);++i) {
    //     printf("%c\n",aclbuf[i]);
    // }
    return 0;
}
