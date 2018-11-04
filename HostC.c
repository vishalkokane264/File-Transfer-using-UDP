#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<unistd.h>  
#define SERV_PORT 49312
#define MAXLINE   1024
int clearbuff(char buff[1024],int size);  
char *END_FLAG = "-----FINISHED------";
int main(int argc, char **argv)
{
    int sockfd,*l;
    struct sockaddr_in servaddr,cliaddr,cliaddr1,temp;
    char ip[50];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.134");//server vishal
    servaddr.sin_port = htons(SERV_PORT);
    cliaddr1.sin_family=AF_INET;
    cliaddr1.sin_addr.s_addr=inet_addr("192.168.1.12");//intermediate brijesh
    cliaddr1.sin_port=htons(SERV_PORT);
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
     
        int n, fd;
    socklen_t len;
    char buf[MAXLINE];

    len=sizeof(cliaddr1);
    n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr1, &len);
    printf("Filename received %s\n",buf);
    int i=0;
    buf[n]=0;
    fd = open(buf, O_RDONLY);
    while ((n = read(fd, buf, MAXLINE)) > 0) {
        sendto(sockfd, buf, n, 0, (struct sockaddr *) &cliaddr1, sizeof(cliaddr1));
 	printf("Sending packets to %s :  %d\n",inet_ntoa(cliaddr1.sin_addr),i);
        i++;
	usleep(1200);
    }
    close(fd);
    return 0;
}
