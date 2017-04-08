//
//  main.cpp
//  http_engine
//
//  Created by Giuseppe Roberti on 05/09/15.
//
//

#include <iostream>
#include "HttpEngine.h"

int main(int argc, const char * argv[]) {
    HttpEngine engine = {argc, argv};
    return engine.run();
}
