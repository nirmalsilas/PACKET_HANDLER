#!/bin/bash
chmod +x PACKET_HANDLER configToolServer
./configToolServer/configToolServer &
./PACKET_HANDLER
