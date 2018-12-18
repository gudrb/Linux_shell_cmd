#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>//getgrgid 함수 사용
#include <pwd.h>//getpwuid 함수 사용
#include <string.h>
void lscommandl()
{

    DIR* dp = NULL; // 내가 보고자 하는 곳
    char path[1024];
    getcwd(path,1024);//현재 주소 path에 받아오기
    struct dirent* entry = NULL;
    struct passwd* user_pw = NULL;
    char gid[50]; // 그룹 id 받아올 곳
    char uid[50]; // 사용자 id 받아올 곳
    struct goup *group_entry = NULL;
    struct stat buf;//entry 구조체에 있는 이름을 buf에 넘겨줌
    char list[400];// 퍼미션 입력할곳
    int index=1;
    int i;

    if((dp=opendir(path)) != NULL)
    {


    while ( (entry = readdir(dp)) != NULL) // dp를 읽었을 때
    {
        if(entry->d_name[0]!='.'){
            stat(entry->d_name, &buf); //파일이름을 stat구조체가 받음
            switch(buf.st_mode&S_IFMT)//파일 타입 추출
            {
                case S_IFREG:
                list[index++]='-';
                break;
                case S_IFDIR:
                list[index++]='d';

            }
             for (i=0; i<3; i++) {
             if (buf.st_mode & (S_IREAD >> i*3))//상수 칸 이동하며 검사
                list[index++] = 'r';
             else
                list[index++] = '-';
             if (buf.st_mode & (S_IWRITE >> i*3))
                list[index++] = 'w';
             else
                list[index++] = '-';
             if (buf.st_mode & (S_IEXEC >> i*3))
                list[index++] = 'x';
             else
                list[index++] = '-';
            }
            list[index] = '\0'; //문자열 끝을 알림
            strcpy(uid,(getpwuid(buf.st_uid))->pw_name);//stat구조체에 있는 id를 이용해 해당하는 이름 얻음
            strcpy(gid,(getgrgid(buf.st_gid))->gr_name);
            printf("%s %lu %s %s %ld %s %s\n",list,buf.st_nlink,uid,gid,buf.st_size,ctime(&buf.st_ctime),entry->d_name);
            index=0;
            }
        }
    closedir(dp);

}}
int main()
{
    lscommandl();
}
