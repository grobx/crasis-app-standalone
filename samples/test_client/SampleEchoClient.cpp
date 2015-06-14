/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "SampleEchoClient.h"

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
    m_context = zmq::context_t(ZMQ_IO_THREADS_DFLT);
    m_dispatcher = EventDispatcher();
}

void SampleEchoClient::initSockets()
{
    auto rep = std::make_shared<zmq::socket_t>(m_context, ZMQ_REQ);
    auto repListener = std::make_unique<SocketListener>();
    
    repListener->onInit = [rep]() {
        std::cout << "Echo Client Socket Initialized!" << std::endl << std::flush;

        rep->connect("tcp://127.0.0.1:5555");
        assert (rep->connected());
    };

    repListener->onSend = [rep]() {
        std::cout << "Echo Client Socket Send Data!" << std::endl << std::flush;

        zmq::message_t msg (12);
        memcpy ((void *) msg.data (), "Hello World!", 12);
        
        rep->send(msg);
    };

    repListener->onRecv = [rep]() {
        std::cout << "Echo Client Socket Recv Data!" << std::endl << std::flush;
        
        zmq::message_t msg;
        rep->recv(&msg);
    };
    
    repListener->onError = [rep]() {
        std::cout << "Echo Client Socket Error!" << std::endl << std::flush;
        
        rep->close();
        rep->connect("tcp://127.0.0.1:5555");
        assert (rep->connected());
    };
    
    m_dispatcher.addListener(std::move(repListener), rep);
}

void SampleEchoClient::loop()
{
    m_dispatcher.loop();
}
