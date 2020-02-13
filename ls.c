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


int isdir(char* path) 
{
    struct stat path_stat;
    if(stat(path,&path_stat)!=0) {

        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    return S_ISDIR(path_stat.st_mode);
}

struct acl *load_acl(char *path)
{
    struct acl *meta = (struct acl *)malloc(sizeof(struct acl));
    int size;
    char buf[0];
    int bool_isdir = 0;
        
    bool_isdir = isdir(path);

    size = getxattr(path, OWNER, &buf, 0);
    ////acl_present(size);
    char *owner = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, OWNER, owner, size);
    owner[size] = '\0';

    size = getxattr(path, NAMED_USERS, &buf, 0);
    ////acl_present(size);
    char *named_users = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, NAMED_USERS, named_users, size);
    named_users[size] = '\0';

    size = getxattr(path, OWNER_GROUP, &buf, 0);
    ////acl_present(size);
    char *owner_group = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, OWNER_GROUP, owner_group, size);
    owner_group[size] = '\0';

    size = getxattr(path, NAMED_GROUPS, &buf, 0);
    ////acl_present(size);
    char *named_groups = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, NAMED_GROUPS, named_groups, size);
    named_groups[size] = '\0';

    size = getxattr(path, MASK, &buf, 0);
    ////acl_present(size);
    char *mask = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, MASK, mask, size);
    mask[size] = '\0';

    size = getxattr(path, OTHERS, &buf, 0);
    ////acl_present(size);
    char *others = (char *)malloc((size + 1) * sizeof(char));
    size = getxattr(path, OTHERS, others, size);
    others[size] = '\0';

    meta->isdir = bool_isdir;
    meta->owner = owner;
    meta->named_users = named_users;
    meta->onwer_group = owner_group;
    meta->named_groups = named_groups;
    meta->mask = mask;
    meta->others = others;

    if (bool_isdir==1) 
    {

        size = getxattr(path, DEFAULT_OWNER, &buf, 0);
        ////acl_present(size);
        char *default_owner = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_OWNER, default_owner, size);
        default_owner[size] = '\0';

        size = getxattr(path, DEFAULT_NAMED_USERS, &buf, 0);
        ////acl_present(size);
        char *default_named_users = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_NAMED_USERS, default_named_users, size);
        default_named_users[size] = '\0';

        size = getxattr(path, DEFAULT_OWNER_GROUP, &buf, 0);
        ////acl_present(size);
        char *default_owner_group = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_OWNER_GROUP, default_owner_group, size);
        default_owner_group[size] = '\0';

        size = getxattr(path, DEFAULT_NAMED_GROUPS, &buf, 0);
        ////acl_present(size);
        char *default_named_groups = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_NAMED_GROUPS, default_named_groups, size);
        default_named_groups[size] = '\0';

        size = getxattr(path, DEFAULT_MASK, &buf, 0);
        ////acl_present(size);
        char *default_mask = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_MASK, default_mask, size);
        default_mask[size] = '\0';

        size = getxattr(path, DEFAULT_OTHERS, &buf, 0);
        ////acl_present(size);
        char *default_others = (char *)malloc((size + 1) * sizeof(char));
        size = getxattr(path, DEFAULT_OTHERS, default_others, size);
        default_others[size] = '\0';

        meta->default_owner = default_owner;
        meta->default_named_users = default_named_users;
        meta->default_onwer_group = default_owner_group;
        meta->default_named_groups = default_named_groups;
        meta->default_mask = default_mask;
        meta->default_others = default_others;
    
    }

    return meta;
}

void stringcat(char* dest, char* s) {
    int l = strlen(dest);
    dest = (char *)realloc(dest,(l+strlen(s)+1)*sizeof(char));
    for(int i=0;i<strlen(s);++i) {
        dest[l+i] = s[i];
    }
    dest[l+strlen(s)] = '\0';
    return;
}

char* display_perm(struct acl* meta){
    char*operm = meta->owner;
    char*gperm = meta->onwer_group;
    char*other = meta->others;
    char*mask = meta->mask;

    char* perm = (char*)malloc(sizeof(char));
    stringcat(perm,operm);
    stringcat(perm,gperm);
    stringcat(perm,other);
    stringcat(perm,mask);
    return perm;
}


int main(int argc, char  *argv[])
{
    struct dirent *de; 

    uid_t ruid = getuid();
    
  
    DIR *dr = opendir(argv[1]); 
  
    if (dr == NULL)   
    { 
        printf("Could not open current directory" ); 
        exit(EXIT_FAILURE); 
    } 

    while ((de = readdir(dr)) != NULL) {
        if(strcmp(de->d_name,"..")!=0 && strcmp(de->d_name,".")!=0) {

            char* path = (char*)malloc(sizeof(char));            
            stringcat(path,argv[1]);
            stringcat(path,"/");
            stringcat(path,de->d_name);

            struct stat filestat;

            if(stat(path,&filestat)!=0) {
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
            // printf("%s\n",path);
            struct acl* meta = load_acl(path);

            printf("owner:%s  group:%s %d   %s   %s\n", user->pw_name, grp->gr_name, size, de->d_name, 
            S_ISDIR(filestat.st_mode)?"directory":"file");
            printf("%s: permissions: %s\n",path,display_perm(meta));
            free(path);
        }
    }

    closedir(dr);  
    
    exit(EXIT_SUCCESS);
}
