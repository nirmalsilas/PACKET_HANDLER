#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "builder.hpp"
#include "logger.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>



namespace packetHandler
{

struct firewalltable {
    uint8_t  index;
    uint32_t srcIp;
    uint32_t dstIp;
    uint16_t srcPort;
    uint16_t dstPort;
    uint8_t  protocol;
    uint8_t  nextAction;
};

class firewallServices : public DaemonBuilder {

    std::list<firewalltable> firewallTable;
    int fwservice;
    sockaddr_un addr;
public:

    firewallServices() {
        LOG_INFO << "Firewall service initialized\n";
    }

    ~firewallServices() override{
        close(fwservice);
        unlink(addr.sun_path); // Clean up socket file on exit

    };

    void build() override 
    {
        LOG_INFO << "Building firewall service...\n";

        fwservice = socket(AF_UNIX, SOCK_DGRAM, 0);
        if (fwservice < 0) {
            LOG_ERROR << "Failed to create socket \n";
            return;
        }

        
        std::memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        std::strncpy(addr.sun_path, "/tmp/firewall.sock", sizeof(addr.sun_path) - 1);

        unlink(addr.sun_path);

        if (bind(fwservice, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
            LOG_ERROR << "failed to bind uds socket for fwservice"<<"\n";
            close(fwservice);
            return;
        }
        LOG_INFO << "UDS socket created and bound at /tmp/firewall.sock"<<"\n";


    }

    void execute();

    void stop() override {
        LOG_INFO << "Stopping firewall service..."<<"\n";
    }

    void configurationHandler(const nlohmann::json& confstr);
};

}
