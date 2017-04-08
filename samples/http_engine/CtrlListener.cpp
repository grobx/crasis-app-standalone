//
//  CtrlListener.cpp
//  crasis
//
//  Created by Giuseppe Roberti on 05/09/15.
//
//

#include "CtrlListener.h"

CtrlListener::CtrlListener (std::shared_ptr<nnxx::socket> socket)
: SocketListener::SocketListener ()
{
    onInit = [socket]() {
        std::cout << "CtrlListener Socket Initialized!" << std::endl << std::flush;
        
        nnxx::endpoint eid = socket->bind("tcp://*:5555");
        assert (eid > 0);
    };

    onSend = [socket]() {
        std::cout << "CtrlListener Socket Send Data!" << std::endl << std::flush;
    };

    onRecv = [socket]() {
        std::cout << "CtrlListener Socket Recv Data!" << std::endl << std::flush;
        
        nnxx::message msg = socket->recv();
        int size = socket->send(std::move(msg));
        assert(size != -1);
    };
}
