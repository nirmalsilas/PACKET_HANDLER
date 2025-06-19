#include<iostream>
#include "builder.hpp"
#include "firewallServices.hpp"
#include "logger.hpp"
#include <nlohmann/json.hpp>
#include <thread>

using namespace packetHandler;

void firewallServices::configurationHandler(const nlohmann::json& confstr) {
    LOG_INFO << "initializing firewall configuration handler...";
        if (confstr.empty()) {
            LOG_ERROR << "Configuration string is empty.";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }

        try 
        {
            const nlohmann::json& configJson = confstr;
            LOG_INFO << "Parsed JSON configuration: " << configJson.dump();
            if (configJson.contains("firewallTable")) {
                firewallTable.clear();
                for (const auto& entry : configJson["firewallTable"]) {
                    firewalltable tableEntry;
                    tableEntry.index = entry.value("index", 0);
                    tableEntry.srcIp = entry.value("srcIp", 0);
                    tableEntry.dstIp = entry.value("dstIp", 0);
                    tableEntry.srcPort = entry.value("srcPort", 0);
                    tableEntry.dstPort = entry.value("dstPort", 0);
                    tableEntry.protocol = entry.value("protocol", 0);
                    tableEntry.nextAction = entry.value("nextAction", 0);

                    firewallTable.push_back(tableEntry);
                }
                LOG_INFO << "Firewall table configured with " << firewallTable.size() << " entries.";
            } else {
                LOG_ERROR << "Configuration JSON does not contain 'firewallTable'.";
            }
        }
        catch (const nlohmann::json::parse_error& e)
        {
            LOG_ERROR << "JSON parsing error: " << e.what();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    
}


void firewallServices::execute() {
    LOG_INFO << "Executing firewall service...";

    // Load configuration from file configuration.json and give it a configuration handler function in new thread

    auto configHandler = [this]() {
        std::ifstream configFile("configuration.json");
        if (!configFile.is_open()) {
            LOG_ERROR << "Failed to open configuration file.";
            return;
        }
        nlohmann::json configJson;
        try {
            configFile >> configJson;
        } catch (const nlohmann::json::parse_error& e) {
            LOG_ERROR << "JSON parsing error: " << e.what();
            return;
        }
        configFile.close();
        configurationHandler(configJson);
    };

    std::thread configThread(configHandler);
    configThread.detach();   
}






