// Udayaan Nath
// 2017119, CSE
// udayaan17119@iiitd.ac.in

#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<sys/types.h>
#include<pwd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

/* 
get sub-array of argv to pass to execv
*/
int get_argv(int start, int end, char* argv[], char* ptr[]) {

    int i;
    int maxlen = 0;
    
    for (i=0;i<end-start;i++){
        ptr[i] = argv[start+i];
    }
    /* argv ends with a NULL pointer, 
    otherwise Bad address in execv */
    ptr[i] = (char*)0; 
    
    return (end-start+1);
}


int main(int argc, char *argv[])
{
    uid_t ruid = getuid();

    struct stat filestat;
    int exit_status;
    if((exit_status = stat(argv[1],&filestat))!=0){
        printf("%s : %s\n", argv[1],strerror(errno));
        exit(EXIT_FAILURE);
    }
    uid_t owner_id = filestat.st_uid;  

    setuid(owner_id);
    
    int fd[2];
    pipe(fd);

    int p = fork();

    if(p==0) {

        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);

        if((exit_status = execv(argv[1],argv+1))!=0) {
            printf("%s\n",strerror(errno));
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    
    else if (p>0) {
        close(fd[1]);
        waitpid(p,&exit_status,0);
        
        char buf[1];
        while(read(fd[0],buf,1)>0) {
            printf("%s",buf);
        }
        printf("\n");

        exit(exit_status);
    }

}