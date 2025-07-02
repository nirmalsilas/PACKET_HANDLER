#include<iostream>
#include "builder.hpp"
#include "firewallServices.hpp"
#include "logger.hpp"
#include <nlohmann/json.hpp>
#include <thread>

using namespace packetHandler;

void firewallServices::configurationHandler(const nlohmann::json& confstr) {
    LOG_INFO << "initializing firewall configuration handler..."<<"\n";
        if (confstr.empty()) {
            LOG_ERROR << "Configuration string is empty."<<"\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            return;
        }

        try 
        {
            const nlohmann::json& configJson = confstr;
            LOG_INFO << "Parsed JSON configuration: " << configJson.dump()<<"\n";
            if (configJson.contains("firewallTable") && configJson["firewallTable"].contains("rules")) {
                for (const auto& entry : configJson["firewallTable"]["rules"]) {
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
                LOG_INFO << "Firewall table configured with " << firewallTable.size() << " entries."<<"\n";
            } 
            else {
                LOG_ERROR << "Configuration JSON does not contain 'firewallTable.rules'."<<"\n";
            }
        }
    
        catch (const nlohmann::json::parse_error& e)
        {
            LOG_ERROR << "JSON parsing error: " << e.what()<<"\n";
        }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


void firewallServices::execute() {
    LOG_INFO << "Executing firewall service..."<<"\n";

    // Load configuration from file configuration.json and give it a configuration handler function in new thread
    /*
    auto configHandler = [this]() {
        std::ifstream configFile("firewall/configuration.json");
        if (!configFile.is_open()) {
            LOG_ERROR << "Failed to open configuration file."<<"\n";
            return;
        }
        nlohmann::json configJson;
        try {
            configFile >> configJson;
        } catch (const nlohmann::json::parse_error& e) {
            LOG_ERROR << "JSON parsing error: " << e.what()<<"\n";
            return;
        }
        configFile.close();
        configurationHandler(configJson);
    };

    std::thread configThread(configHandler);
    */
    LOG_INFO<<"starting firewall serveice to listen\n";
    char buffer[4956];
    while(1)
    {
        sockaddr_un client_addr;
        socklen_t client_len = sizeof(client_addr);
        ssize_t received = recvfrom(fwservice,buffer,sizeof(buffer)-1,0,
                        (struct sockaddr*)&client_addr, &client_len);
         if (received > 0) {
            buffer[received] = '\0'; // Null-terminate
            LOG_INFO << "Received from client: " << buffer<<"\n";
            nlohmann::json json;
            try {
                json = nlohmann::json::parse(std::string(buffer));
                configurationHandler(json);
            } catch (const nlohmann::json::parse_error& e) {
                LOG_ERROR << "JSON parsing error: " << e.what() << "\n";
            }
        } else {
            LOG_ERROR << "Error receiving data\n";
        }
    }

   // configThread.join();   
}






