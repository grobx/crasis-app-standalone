/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#include "Crasis/Application.h"

using namespace Crasis;

int Application::run ()
{
    variables_map vm;
    
    initOptions();
    
    try {
        store(parse_command_line(m_argc, m_argv, m_options), vm);
        notify(vm);
    } catch (const error &ex) {
        std::cerr << ex.what() << std::endl << std::flush;
        return EXIT_FAILURE;
    }
    
    return exec(vm);
}
