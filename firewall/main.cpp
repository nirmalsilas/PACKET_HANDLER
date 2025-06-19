#include<iostream>
#include "logger.hpp"
#include "firewallServices.hpp"


namespace packetHandler {
int main(){
    LOG_INFO << "Starting firewall service...";

    // Create an instance of the firewall service
    firewallServices firewallService;

    // Build the service
    firewallService.build();

    // Execute the service
    firewallService.execute();
    
    return 0;

}
} // namespace packetHandler