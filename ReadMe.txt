the packet handler module enables parsing of incoming pakcet with firewall rules configured
and other parameters also provide counter for specific measurements


I/P -> IP packet with data
configuration -> firewall configuration 
                 counter fetch
modules :
 1. firewall
 2. eth/ip 
 4. application
 5. logger
 6. packet_simulater
        create packet and send to firewall modules for processing .


flow

<--------------------------logger UT MT -------------------->

                           configuration--------------------
                                |            |             |
                               \ /          \ /           \ /  
I/P--> packet_simulater --> firewall --> eth/ip -->application

 


