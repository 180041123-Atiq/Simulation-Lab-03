#include <iostream>
#include <fstream>
using namespace std;

#include "scheduler.h"
#include "server.h"

int main ()
{
	Scheduler *sch = new Scheduler ();
	sch->initialize ();

	Server* s1 = new Server ();
	Server* s2 = new Server ();

    s1->serverId () = 1;
	s2->serverId () = 2;

	s1->createTraceFile ();
	s2->createTraceFile ();

	s1->arrivalMean () = 1.0;
	s2->arrivalMean () = 0;

	s1->departureMean () = 3.0;
	s2->departureMean () = 3.0;

	s1->initialize ();
    s2->initialize();

    s1->next_ = s2;
    s2->prev_ = s1;

	sch->run ();

	s1->report();
	s2->report();

	//cout<<"inside main getting s2's prev's id : "<<s2->prev_->serverId()<<'\n';
	//cout<<"inside main getting Average System Delay : "<<s2->totalSystemDelay()/100.0<<'\n';
	//cout<<"inside main getting Average Queueing Delay for server 1 : "<<s1->totalQueueingDelay()/100.0<<'\n';
	//cout<<"inside main getting Average Queueing Delay for server 2 : "<<s2->totalQueueingDelay()/100.0<<'\n';

	return 0;
}
