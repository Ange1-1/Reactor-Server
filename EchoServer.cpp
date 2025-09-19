#include "EchoServer.h"

EchoServer::EchoServer(std::string_view ip,const uint16_t port,int subthreadnum,int workthreadnum)
                   :tcpserver_(ip,port,subthreadnum),threadpool_(workthreadnum,"WORKS")
{
    // 以下代码不是必须的，业务关心什么事件，就指定相应的回调函数。
    tcpserver_.setnewconnectioncb([this](spConnection conn){this->HandleClose(conn);});
    tcpserver_.setcloseconnectioncb([this](spConnection conn){this->HandleClose(conn);});
    tcpserver_.seterrorconnectioncb([this](spConnection conn){this->HandleError(conn);});
    tcpserver_.setonmessagecb([this](spConnection conn,std::string_view message){this->HandleMessage(conn,message);});
    tcpserver_.setsendcompletecb([this](spConnection conn){this->HandleSendComplete(conn);});
    tcpserver_.settimeoutcb([this](EventLoop *loop){this->HandleTimeOut(loop);});
}

EchoServer::~EchoServer()
{

}

// 启动服务。
void EchoServer::Start()                
{
    tcpserver_.start();
}

 // 停止服务。
 void EchoServer::Stop()
 {
    // 停止工作线程。
    threadpool_.stop();
    std::println("工作线程已停止。");

    // 停止IO线程（事件循环）。
    tcpserver_.stop();
 }

// 处理新客户端连接请求，在TcpServer类中回调此函数。
void EchoServer::HandleNewConnection(spConnection conn)    
{
    // std::cout << "New Connection Come in." << std::endl;
    std::println ("{} new connection(fd={},ip={},port={}) ok.",Timestamp::now().tostring(),conn->fd(),conn->ip(),conn->port());

    // 根据业务的需求，在这里可以增加其它的代码。
}

// 关闭客户端的连接，在TcpServer类中回调此函数。 
void EchoServer::HandleClose(spConnection conn)  
{
    std::println("{} connection closed(fd={},ip={},port={}) ok.",Timestamp::now().tostring(),conn->fd(),conn->ip(),conn->port());
    // std::cout << "EchoServer conn closed." << std::endl;

    // 根据业务的需求，在这里可以增加其它的代码。
}

// 客户端的连接错误，在TcpServer类中回调此函数。
void EchoServer::HandleError(spConnection conn)  
{
    // std::cout << "EchoServer conn error." << std::endl;

    // 根据业务的需求，在这里可以增加其它的代码。
}

// 处理客户端的请求报文，在TcpServer类中回调此函数。
void EchoServer::HandleMessage(spConnection conn,std::string_view message)     
{

    if (threadpool_.size()==0)
    {
        // 如果没有工作线程，表示在IO线程中计算。
        OnMessage(conn,std::string(message));       
    }
    else
    {
        // 把业务添加到线程池的任务队列中，交给工作线程去处理业务。
        threadpool_.addtask([this,conn,message=std::string(message)](){this->OnMessage(conn,message);});
    }
}

 // 处理客户端的请求报文，用于添加给线程池。
 void EchoServer::OnMessage(spConnection conn,std::string_view message)     
 {

    // 在这里，将经过若干步骤的运算。
    std::string newmessage="reply:"+std::string(message);          // 回显业务。
    conn->send(newmessage);   // 把数据发送出去。 
 }

// 数据发送完成后，在TcpServer类中回调此函数。
void EchoServer::HandleSendComplete(spConnection conn)     
{
    // std::cout << "Message send complete." << std::endl;

    // 根据业务的需求，在这里可以增加其它的代码。
}

// epoll_wait()超时，在TcpServer类中回调此函数。
void EchoServer::HandleTimeOut(EventLoop *loop)         
{
    //std::cout << "EchoServer timeout." << std::endl;

    // 根据业务的需求，在这里可以增加其它的代码。
}