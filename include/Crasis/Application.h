/*
 * Copyright (C) 2015 Giuseppe Roberti.
 *
 * See the LICENSE file for terms of use.
 */

#ifndef __Crasis__Application__
#define __Crasis__Application__

#include <iostream>

#include <boost/program_options.hpp>

using namespace boost::program_options;

namespace Crasis {
    class Application
    {
    public:
        Application (int argc, const char **argv) : m_argc(argc), m_argv(std::move(argv)) {};
        
        /**
         * Execute initOptions() to populate m_options.
         * Then retrive options from m_argc, m_argv in variables_map and pass those options
         * to exec().
         * Return the status from exec().
         */
        int run ();
        
    protected:
        /**
         * Populate m_options
         */
        virtual void initOptions () = 0;
        
        /**
         * Exec the program given the variables_map
         */
        virtual int exec (variables_map vm) = 0;
        
    private:
        int m_argc;
        const char **m_argv;
        options_description m_options {"Usage"};
    };
}

#endif /* defined(__Crasis__Application__) */
