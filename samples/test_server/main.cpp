/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "SampleEchoServer.h"

int main(int argc, const char * argv[])
{
    SampleEchoServer app(argc, argv);
    return app.run();
}
