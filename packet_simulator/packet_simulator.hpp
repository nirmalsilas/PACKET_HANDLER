#include<iostream>
#include<vector>

namespace packetHandler
{
    #define IP_DATA_LEN 10
    struct packet
    {
        double protocol;
        uint32_t srcIpAddr;
        uint32_t dstIpAddr;
        std::string payload;
        //packet(uint8_t protocol_, uint32_t srcip_ ,uint32_t dstip_, std::string payload_) : protocol(protocol_), srcIpAddr(srcip_), dstIpAddr(dstip_), payload(payload_){}
        packet(double protocol_) : protocol(protocol_){}
    };
    
    typedef struct 
    { 
        uint8_t   ver_hlen;   /* Header version and length (dwords). */
        uint8_t   service;    /* Service type. */
        uint16_t  length;     /* Length of datagram (bytes). */
        uint16_t  ident;      /* Unique packet identification. */
        uint16_t  fragment;   /* Flags; Fragment offset. */
        uint8_t   timetolive; /* Packet time to live (in network). */
        uint8_t   protocol;   /* Upper level protocol (UDP, TCP). */
        uint16_t  checksum;   /* IP header checksum. */
        uint32_t  src_addr;   /* Source IP address. */
        uint32_t  dest_addr;  /* Destination IP address. */
    } IpHdr; 

    struct IpPkt
    { 
        IpHdr ipHdr; 
        std::string data; 
        IpPkt(IpHdr ip_, std::string data_): ipHdr(ip_), data(data_){}
        

    }; 
    class packet_sim
    {
        public:
        std::vector<IpPkt> packets; 
        void parsexml();
        void packetTx();
        void packetRx();
        void createipv4();
    };
    static std::vector<packet> pktStream;

}
