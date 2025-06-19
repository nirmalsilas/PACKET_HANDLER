#include"logger/logger.hpp"
#include<iostream>
#include<boost/property_tree/ptree.hpp>
#include<packet_simulator.hpp>
#include<firewallServices.hpp>

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
    fwServices->execute();


    LOG_INFO<<"system shutdown ..."<<"\n";
    delete fwServices;
    LOG_INFO<<"system shutdown complete ..."<<"\n";
    return 0;
    


}

