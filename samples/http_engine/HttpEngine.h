/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef __Crasis__Samples__HttpEngine__
#define __Crasis__Samples__HttpEngine__

#include <iostream>
#include <memory>
#include <assert.h>

#include <nnxx/message.h>

#include "Crasis/Application.h"
#include "Crasis/Network/SocketListener.h"
#include "Crasis/Network/EventDispatcher.h"

using namespace Crasis;

/**
 * HttpEngine
 *
 * This Component will provide
 *   - a CtrlService
 *   - a StatsService
 *   - the HttpServer (using libh2o)
 *
 * The CtrlService expose a socket on 55551 and is able to
 * process CtrlInstruction(s) like RegisterRoute.
 *
 * The StatsService expose a socket on 55599 and is able to
 * process StatInstruction(s) like GetStats.
 */
class HttpEngine : public Application
{
public:
    HttpEngine (int argc, const char **argv) : Application (argc, argv) {};
    
    void initOptions ();
    int exec (variables_map vm);

private:
    void initContext ();
    void initSockets ();
    void loop ();
    
    Crasis::Network::EventDispatcher m_dispatcher;
};

#endif /* defined(__Crasis__Samples__HttpEngine__) */
