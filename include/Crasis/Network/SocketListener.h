/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef __Crasis__Network__SocketListener__
#define __Crasis__Network__SocketListener__

#include <functional>
#include <memory>

#include <zmq.hpp>

namespace Crasis {
    namespace Network {
        class SocketListener
        {
        public:
            SocketListener () {};
            
            std::function<void()> onInit;
            std::function<void()> onRecv;
            std::function<void()> onSend;
            std::function<void()> onError;
        };
    }
}

#endif /* defined(__Crasis__Network__SocketListener__) */
