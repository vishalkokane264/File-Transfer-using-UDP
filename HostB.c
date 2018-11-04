#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<unistd.h>  
#define SERV_PORT 49312
#define MAXLINE   1024
int clearbuff(char buff[1024],int size);  
char *END_FLAG = "------FINISHED-------";
int main(int argc, char **argv)
{
    int sockfd,*l;
    struct sockaddr_in servaddr,cliaddr,cliaddr1,cliaddr2,temp;
    char ip[50];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.12");//interm
    servaddr.sin_port = htons(SERV_PORT);

    cliaddr1.sin_family=AF_INET;
    cliaddr1.sin_addr.s_addr=inet_addr("192.168.1.134");//send to server
    cliaddr1.sin_port=htons(SERV_PORT);

    cliaddr2.sin_family=AF_INET;
    cliaddr2.sin_addr.s_addr=inet_addr("192.168.1.22");//send to client
    cliaddr2.sin_port=htons(SERV_PORT);
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
     
        int n, fd;
    socklen_t len;
    char buf[MAXLINE];

    len=sizeof(cliaddr2);
    n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr2, &len);
    printf("Filename received from client : %s\n",buf);
        sendto(sockfd, buf, n, 0, (struct sockaddr *) &cliaddr1, sizeof(cliaddr1));
    strcpy(ip,inet_ntoa(cliaddr1.sin_addr));
    printf("File receiving  from server : %s\n",buf);
    int i=0;
    buf[n]=0;
    len=sizeof(cliaddr1);
    n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr1, &len);
    while (n>0)
    {
        sendto(sockfd, buf, n, 0, (struct sockaddr *) &cliaddr2, sizeof(cliaddr2));
 	printf("Sending packets to %s :  %d\n",inet_ntoa(cliaddr2.sin_addr),i);
        i++;
	usleep(800);
        n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr1, &len);
    }
    close(sockfd);
    return 0;
}
