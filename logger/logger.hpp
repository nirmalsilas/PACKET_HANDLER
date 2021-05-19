#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>

using namespace std;
namespace packetHandler
{

    enum class LOGLEVEL : int
    {
        ERROR = 1,
        WARNING,
        INFO,
        DEBUG
    };

    class logger
    {
        stringstream buffer;
        LOGLEVEL logLevel;
        LOGLEVEL currentLogLevel;
    public:
    
        logger(LOGLEVEL logLevel_) : logLevel(logLevel_) {
        }
        static logger& get(LOGLEVEL log_)
        {
            static logger instance(LOGLEVEL::ERROR);
            instance.currentLogLevel = log_;
            return instance;

        }
        void write2File();
        void setLogLevel(LOGLEVEL log_)
        {
            logLevel = log_;
        }
        template <typename type>
        logger& operator<<(type ss)
        {
            buffer.str("");
            buffer<<ss;
            if(this->currentLogLevel <= logLevel)
            {
                write2File();
            }
            return *this;

        }
    };

#define LOG_INFO logger::get(LOGLEVEL::INFO)<<"[INFO]"<<__FUNCTION__<<" : "
#define LOG_ERROR logger::get(LOGLEVEL::ERROR)<<"[ERROR]"<<__FUNCTION__<<" : "
#define LOG_WARNING logger::get(LOGLEVEL::WARNING)<<"[WARNING]"<<__FUNCTION__<<" : "
#define LOG_DEBUG logger::get(LOGLEVEL::DEBUG)<<"[DEBUG]"<<__FUNCTION__<<" : "
#define SET_LOG_LEVEL(level) logger::get(LOGLEVEL::DEBUG).setLogLevel(level)
}
