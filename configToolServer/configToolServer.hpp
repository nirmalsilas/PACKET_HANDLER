#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdexcept>
#include<cstring>



class configToolServer{
    public:
    
    configToolServer(int port)
    {
        server_fd = socket(AF_INET,SOCK_DGRAM, 0);
        if(server_fd == -1) throw std::runtime_error("failed to create socket");

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if(bind(server_fd,(struct sockaddr*)&address, sizeof(address)) < 0)
            throw std::runtime_error("bind failed");
               
    }

    void sendToFirewall(std::string json)
    {
        const char* fwSocketPath = "/tmp/firewall.sock";
        int clientSocket = socket(AF_UNIX,SOCK_DGRAM,0);
        if(clientSocket<0)
        {
            std::cout<<"failed to create socket\n";
        }
        struct sockaddr_un addr;
        memset(&addr,0,sizeof(addr));
        addr.sun_family =AF_UNIX;
        strncpy(addr.sun_path, fwSocketPath,sizeof(addr.sun_path)-1);
    
        ssize_t sent = sendto(clientSocket, json.c_str(), json.size(), 0, (struct sockaddr*)&addr, sizeof(addr));
        if(sent ==-1) std::cout<<"failed to send to firewall"<<"\n";
        else std::cout<<"data send to firewall\n";

        close(clientSocket);
    }
    std::string reciveJson()
    {
        char buffer[4096];
        sockaddr_in client_addr{};
        socklen_t addr_len =  sizeof(client_addr);

        ssize_t recv_len = recvfrom(server_fd, buffer, 4096 - 1, 0,
                                   (struct sockaddr*)&client_addr, &addr_len);
        
        if (recv_len < 0)
            throw std::runtime_error("recvfrom failed");

        buffer[recv_len] = '\0';
        return std::string(buffer);
    }

    void sendtoFirewall(std::string json);

    ~configToolServer() {
        if (server_fd != -1)
            close(server_fd);
    }
    private:
         int server_fd =-1;
    
};