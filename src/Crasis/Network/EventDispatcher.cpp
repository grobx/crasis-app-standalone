/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "EventDispatcher.h"

using namespace Crasis::Network;

void EventDispatcher::addListener(std::unique_ptr<Crasis::Network::SocketListener> l,
                                  std::shared_ptr<nnxx::socket> s)
{
    m_listeners.insert(std::make_pair(s->fd(), std::move(l)));
    m_sockets.insert(std::make_pair(s->fd(), std::move(s)));
}

void EventDispatcher::loop()
{
    initialize();
    while (true) {
        processEvent();
    }
}

void EventDispatcher::initialize()
{
    // for each listener call onInit
    for (auto& pair : m_listeners) {
        if (pair.second->onInit)
            pair.second->onInit();
    }
}

auto EventDispatcher::itemsToPoll()
{
    // construct items for every sockets in m_listeners
    auto items = std::make_unique<nnxx::pollfd[]>(m_listeners.size());
    int i = 0;
    for (auto& e : m_listeners) {
        items[i].fd = e.first; // operator socket_t::void*
        items[i].events = NN_POLLIN + NN_POLLOUT;
    }
    return items;
}

void EventDispatcher::processEvent()
{
    // now is the time to poll
    auto items = itemsToPoll();
    assert (items.get() != nullptr);
    int tot = nnxx::poll(items.get(), static_cast<int>(m_listeners.size()), -1);
    for (int i,j=i=0; j<tot; ++j) {
        // go until you found an item with event
        while (items[i].revents == 0) ++i;
        assert (i < m_listeners.size());
        
        // get the socket_t associated to ptr items[i].socket
        auto socket_obj = m_sockets[items[i].fd];
        
        // get listeners associated to socket_obj
        assert (m_listeners.count(items[i].fd) >= 1);
        auto listeners_range = m_listeners.equal_range(items[i].fd);
        
        for (auto it = listeners_range.first; it != listeners_range.second; ++it) {
            if (items[i].revents & NN_POLLIN) {
                assert (it->second->onRecv);
                it->second->onRecv();
            }
            if (items[i].revents & NN_POLLOUT) {
                assert (it->second->onSend);
                it->second->onSend();
            }
        }
    }
}
