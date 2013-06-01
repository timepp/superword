#pragma once

#ifndef interface
#define interface struct 
#endif

namespace comp
{
    namespace cmd
    {

        interface Command
        {
            virtual ~Command(){};
            virtual bool Execute(NavigateWnd * pWnd) const = 0;
        };

    }
}
