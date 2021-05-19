#include <iostream>
#include "logger.hpp"
#include "packet_simulator.hpp"
#include<boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

using namespace packetHandler;
#define FILENAME "PACKET_INFO.json"

void packet_sim::parsexml()
{
    boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_json(FILENAME, pt);
    }
    catch(std::exception & e)
    {
        std::cout<<"ERROR while opening json file\n"<<e.what();
        return;
    }
    int i=0;
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &v, pt.get_child("packets"))
       {
            pktStream.emplace_back( v.second.get<std::string>("macaddr") ,
                                    v.second.get<std::string>("ipaddr"),
                                    v.second.get<std::string>("data") );
       }
    
}


