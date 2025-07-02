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
    
    fwclient.join();


    delete fwServices;  
    return 0;


}

