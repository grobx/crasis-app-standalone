/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "SampleEchoServer.h"

using Crasis::Network::EventDispatcher;

void SampleEchoServer::initOptions()
{
}

int SampleEchoServer::exec(variables_map vm)
{
    initContext();
    initSockets();
    loop();
    return EXIT_SUCCESS;
}

void SampleEchoServer::initContext()
{
    m_dispatcher = EventDispatcher();
}

void SampleEchoServer::initSockets()
{
    using SocketListener = Crasis::Network::SocketListener;
    
    auto rep = std::make_shared<nnxx::socket>(nnxx::SP, nnxx::REQ);
    auto repListener = std::make_unique<SocketListener>();
    
    repListener->onInit = [rep]() {
        std::cout << "Echo Server Socket Initialized!" << std::endl << std::flush;
        
        nnxx::endpoint eid = rep->bind("tcp://*:5555");
        assert(eid > 0);
    };

    repListener->onRecv = [rep]() {
        std::cout << "Echo Server Socket Recv Data!" << std::endl << std::flush;

        nnxx::message msg = rep->recv();
        int size = rep->send(msg);
        assert(size != -1);
    };

    repListener->onSend = [rep]() {
        std::cout << "Echo Server Socket Send Data!" << std::endl << std::flush;
    };
    
    m_dispatcher.addListener(std::move(repListener), rep);
}

void SampleEchoServer::loop()
{
    m_dispatcher.loop();
}
