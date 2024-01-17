#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

#include <stdio.h>

#define BUF_SIZE 512
#define Q_SIZE 5

int main(int ac, char **av)
{
    if (ac != 2)
    {
        printf("Usage : %s <port>\n", av[0]);
        return 1;
    }

    int clientSocket, serverSocket, maxFd, strLen, socketNum;
    struct sockaddr_in clientAddr, serverAddr;
    struct timeval timeout;
    fd_set reads, cpy_reads;
    socklen_t addrSize;
    char buf[BUF_SIZE];

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(atoi(av[1]));

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cout << "bind() Error" << std::endl;
        return 1;
    }
    if (listen(serverSocket, Q_SIZE) == -1)
    {
        std::cout << "listen() Error" << std::endl;
        return 1;
    }

    FD_ZERO(&reads);
    FD_SET(serverSocket, &reads); 
    maxFd = serverSocket; 

    while (true)
    {
        cpy_reads = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        socketNum = select(maxFd + 1, &cpy_reads, 0, 0, &timeout);
        if (socketNum == -1)
            break ;
        if (socketNum == 0)
            continue ;

        for (int i = 0; i < maxFd + 1; i++)
        {
            if (FD_ISSET(i,  &cpy_reads) != 0)
            {
                if (i == serverSocket)
                {
                    addrSize = sizeof(clientAddr);
                    clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &addrSize);
                    // fcntl 비블락킹 설정
                    FD_SET(clientSocket, &reads);
                    
                    if (maxFd < clientSocket)
                        maxFd = clientSocket;
                    printf("connected client: %d \n", clientSocket);
                }
                else
                {
                    strLen = read(i, buf, BUF_SIZE);
                    if (strLen == 0) // EOF를 클라이언트가 보냈을 때
                    {
                        FD_CLR(i, &reads);
                        close(i);
                        printf("closed client: %d\n", i);
                    }
                    else
                    {
                        write(i, buf, strLen);
                    }
                }
            }
        }
    }
    close(serverSocket);
    return 0;
}