#include<iostream>
#include<vector>

namespace packetHandler
{
    struct packet
    {
        std::string macAddr;
        std::string ipAddr;
        std::string data;
        packet(std::string mac_, std::string ip_, std::string data_) : macAddr(mac_), ipAddr(ip_), data(data_){}
    };
    
    class packet_sim
    {

    public:
    void parsexml();
    void packetTx();
    void packetRx();
    };
    static std::vector<packet> pktStream;

}
