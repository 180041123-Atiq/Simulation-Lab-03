#include "SimEntity.h"
#include<iostream>

void SimEntity :: set_next(Server* var)
{
    next = var;
}

Server* SimEntity :: get_next()
{
    return next;
}

void SimEntity :: set_prev(Server* var)
{
    prev = var;
}

Server* SimEntity :: get_prev()
{
    return prev;
}

void SimEntity :: send(Item* item)
{
    std::cout<<"inside send SimEntity : "<<item->start_time<<' '<<item->server_id<<"\n";
}

void SimEntity :: recev(Item* item)
{
    std::cout<<"inside recev SimEntity : "<<item->start_time<<' '<<item->server_id<<"\n";
}
