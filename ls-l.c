#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>//getgrgid �Լ� ���
#include <pwd.h>//getpwuid �Լ� ���
#include <string.h>
void lscommandl()
{

    DIR* dp = NULL; // ���� ������ �ϴ� ��
    char path[1024];
    getcwd(path,1024);//���� �ּ� path�� �޾ƿ���
    struct dirent* entry = NULL;
    struct passwd* user_pw = NULL;
    char gid[50]; // �׷� id �޾ƿ� ��
    char uid[50]; // ����� id �޾ƿ� ��
    struct goup *group_entry = NULL;
    struct stat buf;//entry ����ü�� �ִ� �̸��� buf�� �Ѱ���
    char list[400];// �۹̼� �Է��Ұ�
    int index=1;
    int i;

    if((dp=opendir(path)) != NULL)
    {


    while ( (entry = readdir(dp)) != NULL) // dp�� �о��� ��
    {
        if(entry->d_name[0]!='.'){
            stat(entry->d_name, &buf); //�����̸��� stat����ü�� ����
            switch(buf.st_mode&S_IFMT)//���� Ÿ�� ����
            {
                case S_IFREG:
                list[index++]='-';
                break;
                case S_IFDIR:
                list[index++]='d';

            }
             for (i=0; i<3; i++) {
             if (buf.st_mode & (S_IREAD >> i*3))//��� ĭ �̵��ϸ� �˻�
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
            list[index] = '\0'; //���ڿ� ���� �˸�
            strcpy(uid,(getpwuid(buf.st_uid))->pw_name);//stat����ü�� �ִ� id�� �̿��� �ش��ϴ� �̸� ����
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
