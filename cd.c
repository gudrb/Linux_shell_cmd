#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void changedir();

int main(int argc,char*argv[]){
 changedir();}




void changedir(){
        int chk;
        char path[1024];
        getcwd(path,1024);//현재 주소 path에 받아오기
        chk =chdir(path); //path 자리에 argv 가 들어가야함
        if(chk!=0){
                printf("cd fail\n");
        }
}
