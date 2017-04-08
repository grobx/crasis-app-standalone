//
//  EventDispatcherNext.h
//  crasis
//
//  Created by Giuseppe Roberti on 29/06/15.
//
//

#ifndef crasis_EventDispatcherNext_h
#define crasis_EventDispatcherNext_h

/*
 RENAME listener AS consumers ?

 A SocketConsumer is an object, associated with a Socket, that is able to recv/send messages
 control socket options, etc ..
 When you want to send a message you use SocketConsumer->send(Message msg)
 This will queue the message in SocketConsumer queue and when the EventDispatcher found that
 a Socket is able to send a message (NN_POLLOUT) it will send.

 Q: But, why does we need SocketConsumer instead of use socket directly ?
 */


/*
 SPLIT listener INTO sender, reader AND ctrl

 SocketSender is able to send messages.
 ??? send (Message msg): send the message through the socket
 onPre (PreSendEvent e): executed before the message was sent
 onPost (PostSendEvent e): executed after the message was sent

 SocketReader is able to read messages.
 Message read():
 onPre (PreReadEvent e): executed before the socket->read() call
 onPost (PostReadEvent e): executed after the socket->read() call

 class SocketCtrl: This is able to control socket options
 ??? setOption (...):

 PreSendEvent:
 SocketSender sender: the sender object
 Message msg: the message that is to send

 PostSendEvent:
 SocketSender sender: the sender object
 int size: the size

 PreReadEvent:
 SocketReceiver receiver:
 Message msg:

 Doing so we will need to implement a SocketSender if we wish to recv
 */


#endif
