// 回显业务的客户端程序。
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include<string>
#include<vector>
#include<print>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::println("usage:./client ip port");
        std::println("example:./client 192.168.150.128 5085\n");
        return -1;
    }

    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::println("socket() failed.");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        std::println("connect({}:{}) failed.", argv[1], argv[2]);
        close(sockfd);
        return -1;
    }

    std::println("connect ok.");
    std::println("开始时间：{}", time(0));

    for (int ii = 0; ii < 10; ii++)
    {
        std::string message="这是第"+std::to_string(ii)+"个超级女生。";//创建一个消息
        int len = message.size();//消息长度
        
        /* 使用byte数组来构建缓冲区，二进制专用，但更推荐用string
        std::vector<std::byte> buf(4+len);//缓冲区:头部+内容
        //拼接头部
        memcpy(buf.data(), &len, 4);
        //拼接内容
        memcpy(buf.data()+4, message.c_str(), len);
        send(sockfd, buf.data(), len+4, 0); // 把请求报文发送给服务端。
        recv(sockfd, &len, 4, 0); // 先读取4字节的报文头部。
        buf.resize(len);//重新分配缓冲区大小
        recv(sockfd,buf.data(), len, 0);//读取内容
        message = std::string(buf.begin(), buf.end());//转为字符串
        */

        // 使用 std::string 来构建缓冲区，更安全简洁
        std::string buf;
        buf.append(reinterpret_cast<const char*>(&len), sizeof(len));
        buf.append(message);
        send(sockfd, buf.data(), buf.size(), 0); // 把请求报文发送给服务端。
        recv(sockfd, &len, 4, 0); // 先读取4字节的报文头部。
        message.resize(len); // 调整字符串大小以容纳接收的数据
        recv(sockfd, message.data(), len, 0);//读取内容


        std::println("recv:{}", message);
       
    }
    std::println("结束时间：{}", time(0));
}
