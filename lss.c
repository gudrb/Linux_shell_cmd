#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int count;
void lscommand()
{
    DIR* dp =NULL;// 자식이 현제 가리키는 곳

    char **strsort;
    char *temp;
    int i,j,k,h;
    int sortindex=0;
    int buff_size = 1024;
    char path[1024];
    getcwd(path,1024);
    struct dirent* entry = NULL;

    temp = malloc(buff_size+5);
    strsort=(char**)malloc(100*sizeof(*strsort));
    for(i=0;i<100;i++)
        strsort[i]=(char*)malloc(10000*sizeof(**strsort));

    if((dp=opendir(path))!=NULL && (dp=opendir(path))!=NULL ){
    while((entry = readdir(dp)) != NULL)
    {
      strsort[sortindex++] = entry->d_name;

    }

    for(k=0;k<sortindex;k++)
        for(h=0;h<sortindex-1;h++)
        {

          if(strcmp(strsort[h],strsort[h+1])>0)
          {
              temp = strsort[h+1];
              strsort[h+1] = strsort[h];
              strsort[h] = temp;

          }
        }

    count=1;
    for(j=0;j<sortindex;j++)
    {
        if(strsort[j][0] != '.')
            {
                if((count%5) == 0)
                {
                    printf("%s\n", strsort[j]);
                    count = 0;
                }
                else
                {
                    printf("%-16s", strsort[j]);
                }
                count++;
           }
    }


       closedir(dp);
       printf("\n");
}
}
void main()
{
    lscommand();
}
