/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "SampleRouter.h"

using Crasis::Network::EventDispatcher;
using Crasis::Network::SocketListener;

void SampleRouter::initOptions()
{
}

int SampleRouter::exec(variables_map vm)
{
    initContext();
    initSockets();
    loop();
    return EXIT_SUCCESS;
}

void SampleRouter::initContext()
{
    m_dispatcher = EventDispatcher();
}

void SampleRouter::initSockets()
{
    auto rep = std::make_shared<nnxx::socket>(nnxx::SP, nnxx::REP);
    auto repListener = std::make_unique<RouterListener>();
    
    repListener->onInit = [rep]() {
        std::cout << "Router Socket Initialized!" << std::endl << std::flush;
        
        nnxx::endpoint eid = rep->connect("tcp://127.0.0.1:5555");
        assert (eid > 0);
    };
    
    repListener->onSend = [rep]() {
        std::cout << "Router Socket Send Data!" << std::endl << std::flush;
        
        nnxx::message msg (12);
        memcpy ((void *) msg.data (), "Hello World!", 12);
        
        int size = rep->send(msg);
        assert(size != -1);
    };
    
    repListener->onRecv = [](const RecvEvent& e) {
        /*
         Here we need to do the hard thing to recv the message, parse into
         an object of type Instruction and call the related callback
         */
        std::cout << "Router Socket Recv Data!" << std::endl << std::flush;
        
        nnxx::message msg = e->msg();
        RouterListener listener = e->listener();
        
        auto instr = listener->parse(msg);
        auto res = listener->process(std::move(instr));
    };
    
    repListener->onError = [rep]() {
        std::cout << "Router Socket Error!" << std::endl << std::flush;
        
        rep->close();
        nnxx::endpoint eid = rep->connect("tcp://127.0.0.1:5555");
        assert (eid > 0);
    };
    
    m_dispatcher.addListener(std::move(repListener), rep);
}

void SampleRouter::loop()
{
    m_dispatcher.loop();
}
