#include <iostream>
#include "logger.hpp"
#include "packet_simulator.hpp"
#include<boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

using namespace packetHandler;
#define FILENAME "PACKET_INFO.xml"

void packet_sim::parsexml()
{
       boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_xml( FILENAME, pt  );
    }
    catch(std::exception & e)
    {
        std::cout<<"ERROR while opening xml file\n"<<e.what();
        return;
    }

        
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt.get_child("packets"))
    {
        
        LOG_INFO<<"DEBUG payload is "<<v.first<<"\n";
        pktStream.emplace_back( v.second.get<double>("protocol")
                                //v.second.get<string>("srcIpAddr"),
                                    //v.second.get<long double>("dstIpAddr"),
                                    //v.second.get<std::string>("payload") 
                                    );
        LOG_INFO<<"DEBUG value : "<<pktStream[0].protocol<<pktStream[0].srcIpAddr <<pktStream[0].dstIpAddr<<"\n";

    }


  
    
}

void packet_sim::createipv4()
{
    for(auto pkt : pktStream)
    {
        IpHdr ip;
        ip.ver_hlen =0x45;
        ip.protocol =pkt.protocol;
        ip.src_addr = pkt.srcIpAddr;
        ip.dest_addr = pkt.dstIpAddr;
        packets.emplace_back(ip, pkt.payload);

    }

}
void packet_sim::packetRx()
{

    
}
