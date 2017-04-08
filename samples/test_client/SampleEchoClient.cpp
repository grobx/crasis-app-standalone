/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "SampleEchoClient.h"

#include <nanomsg/nn.h>

using Crasis::Network::EventDispatcher;
using Crasis::Network::SocketListener;

void SampleEchoClient::initOptions()
{
}

int SampleEchoClient::exec(variables_map vm)
{
    initContext();
    initSockets();
    loop();
    return EXIT_SUCCESS;
}

void SampleEchoClient::initContext()
{
    m_dispatcher = EventDispatcher();
}

void SampleEchoClient::initSockets()
{
    auto rep = std::make_shared<nnxx::socket>(nnxx::SP, nnxx::REP);
    auto repListener = std::make_unique<SocketListener>();
    
    repListener->onInit = [rep]() {
        std::cout << "Echo Client Socket Initialized!" << std::endl << std::flush;

        nnxx::endpoint eid = rep->connect("tcp://127.0.0.1:5555");
        assert (eid > 0);
    };

    repListener->onSend = [rep]() {
        std::cout << "Echo Client Socket Send Data!" << std::endl << std::flush;

        nnxx::message msg (12);
        memcpy ((void *) msg.data (), "Hello World!", 12);
        
        int size = rep->send(msg);
        assert(size != -1);
    };

    repListener->onRecv = [rep]() {
        std::cout << "Echo Client Socket Recv Data!" << std::endl << std::flush;
        
        nnxx::message msg = rep->recv();
    };
    
    m_dispatcher.addListener(std::move(repListener), rep);
}

void SampleEchoClient::loop()
{
    m_dispatcher.loop();
}
