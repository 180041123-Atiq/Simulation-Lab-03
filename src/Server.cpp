#include "server.h"
#include "scheduler.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


Server :: Server () : a_(this), d_(this)
{
	queue_ = new Queue ();
}

double
Server :: exponential(double mean) {

	double r = (double)rand()/RAND_MAX;

	double ex = -1 * mean * log (r);

	return ex;
}

void
Server :: initialize () {

    if(serverId_ == 1)
	{
	    status_ = 0;
        itemArrived_ = 0;
        totalQueueingDelay_ = 0.0;
        totalQueueingLength_ = 0;

        double t = exponential (arrivalMean_);
        //trace_ << "interarrival time " << t << endl;
        a_.activate (t);
	}
	else
    {
        //when we are inside server 2
        //and server 2 has no arrival

        status_ = 0;
        itemArrived_ = 0;
        totalSystemDelay_ = 0.0;
        totalQueueingDelay_ = 0.0;
        totalQueueingLength_ = 0;
    }
}

void
Server :: createTraceFile () {

    if(serverId_ == 1)
	{
	    trace_.open ("trace1.out", ios::out);
        if (!trace_) {
            cout << "cannot open the trace file.\n";
        }
        trace_<< "trace file for the simulation" << endl;
        trace_ << "format of the file" << endl;
        trace_ << "<event> <time> <item id> <server status> <queue size><server id>" << endl << endl;
	}
	else
    {
        trace_.open ("trace2.out", ios::out);
        if (!trace_) {
            cout << "cannot open the trace file.\n";
        }
        trace_<< "trace file for the simulation" << endl;
        trace_ << "format of the file" << endl;
        trace_ << "<event> <time> <item id> <server status> <queue size><server id>" << endl << endl;
    }
}

void
Server :: arrivalHandler () {

	//these things are for lab 03 following the subsequent class

	Item* temp = createJob();

	processJob(temp);

	if(temp->id_ < 100)
    {
        schedule_new_arrival();
    }
}

void
Server :: departureHandler () {

	//these things are for lab 03 following subsequent class

	if(serverId_ == 1)
    {
        // write to the trace file
        if (queue_->length() > 0) {
            trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << "\t" << serverId_ << endl;
        } else {
            trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << "\t" << serverId_ << endl;
        }

        if (queue_->length() > 0) {
            itemInService_ = queue_->deque ();

            //calculating queue_exit time for queue 1
            itemInService_->queue_exit = Scheduler::now();

            // write to the trace file
            trace_ << "s\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << "\t" << serverId_ << endl;

            double t = exponential (departureMean_);
            //trace_ << "\tservice time = " << t << endl;
            d_.activate (t);
        } else {
            status () = 0;
            itemInService_ = 0;
        }

        if(itemInService_ != 0)
        {
            updateStat(itemInService_);
            send(itemInService_);
        }
    }
    else
    {
        //when we are inside server 2

        // write to the trace file
        if (queue_->length() > 0) {
            trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << "\t" << serverId_ << endl;
        } else {
            trace_ << "d\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << "\t" << serverId_ << endl;
        }

        if (queue_->length() > 0) {
            itemInService_ = queue_->deque ();

            //calculating queue_exit time for queue 2
            itemInService_->queue_exit2 = Scheduler::now();

            // write to the trace file
            trace_ << "s\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << "\t" << serverId_ << endl;

            double t = exponential (departureMean_);
            //trace_ << "\tservice time = " << t << endl;
            d_.activate (t);
        } else {
            status () = 0;
            itemInService_ = 0;
        }

        if(itemInService_ != 0)updateStat(itemInService_);
    }
}

void Server :: updateStat(Item* temp)
{
    if(serverId_ == 1)
    {
        totalQueueingDelay_ += (double) ( temp->queue_exit - temp->start_time);
        totalQueueingLength_ += (int) (queue_->length());

    }
    else
    {
        totalQueueingDelay_ += (double) (temp->queue_exit2 - temp->start_time2);
        totalSystemDelay_ += (double)( Scheduler::now() - temp->start_time );
        totalQueueingLength_ += (int) (queue_->length());
    }
}

void Server :: send(Item* item)
{
    //std::cout<<"inside send Server "<<serverId_<<" : "<<item->start_time<<"\n";

    next_->recev(item);
}

void Server :: recev(Item* item)
{
    //std::cout<<"inside recev Server "<<serverId_<<" : "<<item->start_time<<"\n";

    item->start_time2 = Scheduler::now();

    processJob(item);
}


void Server :: test(Item* var)
{
    cout<<"inside test : "<<serverId()<<"\n";
}

void Server :: schedule_new_arrival()
{
    double t = exponential(arrivalMean());
    a_.activate(t);
}

Item* Server :: createJob()
{
    Item* temp;

	itemArrived_++;
	temp = (Item*) malloc (sizeof(Item));
	temp->id_ = itemArrived_;
	temp->start_time = Scheduler::now();
	temp->server_id = serverId_;

    return temp;
}

void Server :: processJob(Item* temp)
{
    //cout<<temp->id_<<"\n";

    trace_ << "a\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length()<< "\t" << serverId_ << endl;

	if (status () == 0) {
		// write to the trace file
		status() = 1;
		trace_ << "s\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << "\t" << serverId_ << endl;
		itemInService_ = temp;

		double t = exponential (departureMean_);
		//trace_ << "\tservice time = " << t << endl;
		d_.activate (t);
	} else {
		queue_->enque(temp);
	}
}

void Server :: report()
{
    if(serverId_ == 1)
    {
        //cout<<"for server 1 report has been called"<<endl;

        trace_<<endl;
        trace_<<endl;

        trace_<<"Avarage Queueing Delay for Server 1 : "<<totalQueueingDelay_/100.0<<endl;
        trace_<<"Avarage Queueing Length for Server 1 : "<<(double) ( (totalQueueingLength_*(1.0)) / Scheduler::now() )<<endl;
    }
    else
    {
        //cout<<"for server 2 report has been called"<<endl;

        trace_<<endl;
        trace_<<endl;

        trace_<<"Average Queueing Delay for Server 2 : "<<totalQueueingDelay_/100.0<<endl;
        trace_<<"Avarage Queueing Length for Server 2 : "<<(double) ( (totalQueueingLength_*(1.0)) / Scheduler::now() )<<endl;
        trace_<<"Avarage System Delay : "<<totalSystemDelay_/100.0<<endl;

    }
}
