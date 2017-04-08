/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef __Crasis__Samples__SampleEchoClient__
#define __Crasis__Samples__SampleEchoClient__

#include <iostream>
#include <memory>
#include <assert.h>

#include <nnxx/message.h>

#include "Crasis/Application.h"
#include "Crasis/Network/SocketListener.h"
#include "Crasis/Network/EventDispatcher.h"
#include "Crasis/Network/RecvEvent.h"

using namespace Crasis;

class SampleRouter : public Application
{
public:
    SampleRouter (int argc, const char **argv) : Application (argc, argv) {};
    
    void initOptions ();
    int exec (variables_map vm);
    
private:
    void initContext ();
    void initSockets ();
    void loop ();
    
    Crasis::Network::EventDispatcher m_dispatcher;
};

class Instruction
{
    
};

class RouterListener : public Crasis::Network::SocketListener
{
public:
    auto parse (nnxx::message& msg) { return std::make_unique<Instruction>(); };
    auto process (std::unique_ptr<Instruction> instr) { return "done"; };
};

#endif /* defined(__Crasis__Samples__SampleEchoClient__) */
