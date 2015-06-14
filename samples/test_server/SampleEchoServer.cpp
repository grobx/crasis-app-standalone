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
    m_context = zmq::context_t(ZMQ_IO_THREADS_DFLT);
    m_dispatcher = EventDispatcher();
}

void SampleEchoServer::initSockets()
{
    using SocketListener = Crasis::Network::SocketListener;
    
    auto rep = std::make_shared<zmq::socket_t>(m_context, ZMQ_REP);
    auto repListener = std::make_unique<SocketListener>();
    
    repListener->onInit = [rep]() {
        std::cout << "Echo Server Socket Initialized!" << std::endl << std::flush;
        
        rep->bind("tcp://*:5555");
    };

    repListener->onRecv = [rep]() {
        std::cout << "Echo Server Socket Recv Data!" << std::endl << std::flush;

        zmq::message_t msg;
        rep->recv(&msg);
        
        rep->send(msg);
    };

    repListener->onSend = [rep]() {
        // This never get called for ZMQ_REP binded socket
        std::cout << "Echo Server Socket Send Data!" << std::endl << std::flush;
    };
    
    repListener->onError = [rep]() {
        std::cout << "Echo Server Socket Error!" << std::endl << std::flush;
        
        rep->close();
        rep->bind("tcp://*:5555");
    };
    
    m_dispatcher.addListener(std::move(repListener), rep);
}

void SampleEchoServer::loop()
{
    m_dispatcher.loop();
}
