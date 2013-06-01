#pragma once

#ifndef interface
#define interface struct 
#endif

namespace comp
{
    namespace cond
    {

        interface Condition
        {
            virtual ~Condition(){};
            virtual bool Meet(const void * pTestee) const = 0;
        };

    }
}
