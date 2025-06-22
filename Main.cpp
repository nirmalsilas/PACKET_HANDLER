#include"logger/logger.hpp"
#include<iostream>
#include<boost/property_tree/ptree.hpp>
#include<packet_simulator.hpp>
#include<firewallServices.hpp>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>
#include<thread>

using namespace packetHandler;
int main()
{
    SET_LOG_LEVEL(LOGLEVEL::INFO);
    LOG_INFO<<"system startup ..."<<"\n";
    packet_sim pkt;
    LOG_INFO<<"packet simulator ..."<<"\n";
    pkt.parsexml();
    

    DaemonBuilder* fwServices = new firewallServices();
    LOG_INFO<<"firewall services ..."<<"\n";
    fwServices->build();
    LOG_INFO<<"firewall services executed ..."<<"\n";
    std::thread fwclient(&DaemonBuilder::execute, fwServices);
    sleep(5);
    const char* fwSocketPath = "/tmp/firewall.sock";
    int clientSocket = socket(AF_UNIX,SOCK_DGRAM,0);
    if(clientSocket<0)
    {
        LOG_ERROR<<"failed to create socket\n";
    }
    struct sockaddr_un addr;
    memset(&addr,0,sizeof(addr));
    addr.sun_family =AF_UNIX;
    strncpy(addr.sun_path, fwSocketPath,sizeof(addr.sun_path)-1);
    const char* msg = "hello firewall good morning";
    ssize_t sent = sendto(clientSocket,msg,strlen(msg),0, (struct sockaddr*)&addr,sizeof(addr));
    if(sent ==-1) LOG_ERROR<<"failed to send to firewall"<<"\n";
    else LOG_INFO<<"data send to firewall\n";

    close(clientSocket);
    fwclient.join();


    delete fwServices;  
    return 0;


}

