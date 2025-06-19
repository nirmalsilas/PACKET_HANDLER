#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "builder.hpp"
#include "logger.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

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
public:

    firewallServices() {
        LOG_INFO << "Firewall service initialized";
    }

    ~firewallServices() noexcept override = default;

    void build() override {
        LOG_INFO << "Building firewall service...";
    }

    void execute();

    void stop() override {
        LOG_INFO << "Stopping firewall service...";
    }

    void configurationHandler(const nlohmann::json& confstr);
};

}
