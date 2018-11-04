#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h> 
#define SERV_PORT 49312
#define MAXLINE   1024
#include<unistd.h>  
char *END_FLAG = "----------FINISHED----------";
         
int main(int argc, char **argv)
{
 
    int n, fd;
    socklen_t len;
    char buf[MAXLINE];
    int sockfd;
    struct sockaddr_in servaddr, cliaddr,cliaddr1,temp_cli;
    char ip[50];
    char target[50];
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("192.168.1.22");//client pratik
    servaddr.sin_port = htons(SERV_PORT);
    cliaddr1.sin_family=AF_INET;
    cliaddr1.sin_addr.s_addr=inet_addr("192.168.1.12");//intermediate brijesh
    cliaddr1.sin_port=htons(SERV_PORT);
    bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("Enter filename of server's machine : ");
    scanf("%s",target);
    sendto(sockfd, target, strlen(target), 0, (struct sockaddr *) &cliaddr1, sizeof(cliaddr1));
    len =sizeof(cliaddr1);
    fd = open(target, O_RDWR | O_CREAT | S_IRUSR, 0666);
    printf("\nReceiving packet from %s\n",inet_ntoa(cliaddr1.sin_addr));
    int i=0;
    while ((n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) &cliaddr1, &len))) {
	buf[n] = 0;
	i++;
        if (strcmp(buf, END_FLAG)==0)
        {
	break;
        }
        write(fd, buf, n);
    }
close(fd); 
   close(sockfd);
    return 0;
}
