#include "configToolServer.hpp"
#include <iostream>
#include<string>


int main()
{

    try{

        configToolServer server(8080);

        std::cout<<"configTool server is up \n";

        while(true)
        {
            std::string json = server.reciveJson();
            std::cout<<"config is : "<<json <<std::endl;
            server.sendToFirewall(json);

        }
    }catch (const std::exception& ex) {
     
        std::cerr << ex.what() << std::endl;
    }
    return 0;

}