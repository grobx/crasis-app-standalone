//
//  Observable.h
//  crasis
//
//  Created by Giuseppe Roberti on 16/06/15.
//
//

#ifndef crasis_Observable_h
#define crasis_Observable_h

#include <memory>

#include <zmq.hpp>

class Subscriber
{
    
};

template <typename T>
class Observable : public std::shared_ptr<T>
{
public:
    void addSubscriber (const Subscriber& s) { m_subscriber(s); };
    
private:
    Subscriber m_subscriber;
};


//class ObservableSocket : public zmq::socket_t, public Observable
//{
//    
//};

#endif
