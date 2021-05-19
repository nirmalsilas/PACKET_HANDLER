#include"logger/logger.hpp"
#include<iostream>
#include<boost/property_tree/ptree.hpp>
#include<packet_simulator.hpp>
using namespace packetHandler;
int main()
{
    SET_LOG_LEVEL(LOGLEVEL::INFO);
    LOG_INFO<<"system startup ..."<<"\n";
    packet_sim pkt;
    pkt.parsexml();


}

