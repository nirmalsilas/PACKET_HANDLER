#include"logger.hpp"
#include<fstream>

using namespace packetHandler;

void logger::write2File()
{
   std::fstream myfile("SYSLOG.txt",std::ios_base::out | std::ios_base::app);
   myfile <<this->buffer.str();
}

