#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>

#define BUF_SIZE 512

int main(int argc, char** argv)
{
    int serverSock, recvLen, recvCnt;
    socklen_t strLen;
    char message[BUF_SIZE];
    struct sockaddr_in serverAddr;

    if (argc != 3)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    serverSock = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSock == -1)
    {
        std::cout << "socket() Error" << std::endl;
    }

    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(atoi(argv[2]));

    if (connect(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cout << "connect() Error" << std::endl;
    } else
    {
        puts("Connected...");
    }

    while(1)
    {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            break;
        }

        strLen = write(serverSock, message, strlen(message));

        recvLen = 0;
        while (recvLen < strLen)
        {
            recvCnt = read(serverSock, &message[recvLen], BUF_SIZE - 1);
            if (recvCnt == -1)
            {
                std::cout << "read() Error" << std::endl;
            }
            recvLen += recvCnt;
        }
        message[recvLen] = 0;
        std::cout << "Message from server: " << message << std::endl;
    }
    close(serverSock);
    return (0);
}