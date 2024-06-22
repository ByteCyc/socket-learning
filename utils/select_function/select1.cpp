#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define buf_size 30

int main(int argc,char* argv[]){
    fd_set reads,temps;
    int result,str_len;
    char buff[buf_size+1];
    struct timeval timeout;
    FD_ZERO(&reads);
    // 这里是对某一个文件操作符监听。
    FD_SET(0, &reads);
    while(1){
        temps = reads;
        timeout.tv_sec=10;
        timeout.tv_usec=0;
        
        result = select(1, &temps, 0, 0, &timeout);
        // 监听失败，函数执行错误,未知原因
        if(result < 0){
            perror("select() error");
        }
        // 函数超时
        else if(result == 0){
            puts("timeout");
        }
        // 这里成功监听到socket描述符发生了变化
        else{
            if(FD_ISSET(0, &temps)){
                // 这里去读取buf_size 长度的缓存，但是可能没有这么多数据，str_len 返回实际读取的字节的长度。
                // int str_len=read(0, buff, buf_size);
                str_len = read(0, buff, buf_size);
                buff[str_len] = 0;
                printf("message from console: %s",buff);
            }
        }
    }
    return 0;
}