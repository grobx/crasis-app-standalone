//
//  CtrlListener.h
//  crasis
//
//  Created by Giuseppe Roberti on 05/09/15.
//
//

#ifndef __crasis__CtrlListener__
#define __crasis__CtrlListener__

#include <iostream>
#include <memory>
#include <assert.h>

#include <nnxx/message.h>
#include <nnxx/socket.h>

#include "Crasis/Network/SocketListener.h"

using namespace Crasis::Network;

class CtrlListener : public SocketListener
{
public:
    CtrlListener (std::shared_ptr<nnxx::socket> socket);
};

#endif /* defined(__crasis__CtrlListener__) */
