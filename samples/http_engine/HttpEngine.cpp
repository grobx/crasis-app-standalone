/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "HttpEngine.h"
#include "CtrlListener.h"

using Crasis::Network::EventDispatcher;
using Crasis::Network::SocketListener;

void HttpEngine::initOptions()
{
}

int HttpEngine::exec(variables_map vm)
{
    initContext();
    initSockets();
    loop();
    return EXIT_SUCCESS;
}

void HttpEngine::initContext()
{
    m_dispatcher = EventDispatcher();
}

void HttpEngine::initSockets()
{
    auto ctrlSocket = std::make_shared<nnxx::socket>(nnxx::SP, nnxx::REP);
    auto ctrlListener = std::make_unique<CtrlListener>(ctrlSocket);
    m_dispatcher.addListener(std::move(ctrlListener), ctrlSocket);
}

void HttpEngine::loop()
{
    m_dispatcher.loop();
}
