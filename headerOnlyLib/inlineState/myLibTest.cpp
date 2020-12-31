//
// Created by weining on 31/12/20.
//

#include <iostream>
#include <common.hh>
#include <myLib.hh>

int main()
{
    {
        // some middleware library may have already enqueued its task therefore
        // the total number of tasks can be greater than 0
        auto sz = common::numTasks();
        myLib::createTask( 100 );
        //common::pushBackTask( 1 );

        std::cout << common::numTasks() << '\n';
    }

    {
        auto sz = common::numTasks();
        myLib::createTask3( 1, 2, 3 );
        // common::pushBackTask( 1 );

        std::cout << common::numTasks() << '\n';
    }
    return 0;
}
