/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef __Crasis__Network__EventDispatcher__
#define __Crasis__Network__EventDispatcher__

#include <map>
#include <list>
#include <vector>
#include <queue>
#include <memory>
#include <tuple>

#include "Crasis/Network/SocketListener.h"

namespace Crasis {
    namespace Network {
        class EventDispatcher
        {
        public:
            void addListener (std::unique_ptr<Crasis::Network::SocketListener> l, std::shared_ptr<zmq::socket_t> s);
            
            void loop ();
            void initialize ();
            void processEvent ();
            
        private:
            std::map<
            void*, // the ptr of socket_t
            std::shared_ptr<zmq::socket_t>
            > m_sockets;

            std::multimap<
            void*, // the ptr of socket_t
            std::unique_ptr<Crasis::Network::SocketListener>
            > m_listeners;
            
            auto itemsToPoll ();
            void executeCallback (std::function<Crasis::Network::SocketListener> fn);
        };
    }
}

#endif /* defined(__Crasis__Network__EventDispatcher__) */
