#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void changedir();

int main(int argc,char*argv[]){
 changedir();}




void changedir(){
        int chk;
        char path[1024];
        getcwd(path,1024);//���� �ּ� path�� �޾ƿ���
        chk =chdir(path); //path �ڸ��� argv �� ������
        if(chk!=0){
                printf("cd fail\n");
        }
}
