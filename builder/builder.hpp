#pragma once
#include<iostream>



class DaemonBuilder {
public:
    virtual ~DaemonBuilder() = default;
    virtual void build() = 0;
    virtual void execute() = 0;
    virtual void stop() = 0;
};

