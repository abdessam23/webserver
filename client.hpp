#pragma once 
#include <iostream>
#include <map>

class Client
{
    private:
        std::string write_buff;
        std::string read_buff;
    public:
        Client();

        ~Client();
};

Client::Client()
{
}

Client::~Client()
{
}
