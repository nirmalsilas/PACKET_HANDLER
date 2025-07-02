#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main( int argc, char* argv[])
{

    if(argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port> <json_file>\n";
        return 1;
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);
    const char* json_file = argv[3];


    std::ifstream file(json_file);
    if(!file)
    {
        std::cerr << "Failed to open file: " << json_file << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid server IP address\n";
        close(sock);
        return 1;
    }

    ssize_t sent = sendto(sock,json.c_str(),json.size(), 0,
                        (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (sent < 0) {
        std::cerr << "Failed to send data\n";
        close(sock);
        return 1;
    }

    std::cout << "JSON sent to " << server_ip << ":" << port << std::endl;
    close(sock);
    return 0;

}