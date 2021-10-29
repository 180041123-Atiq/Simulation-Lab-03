#ifndef server_h
#define server_h

#include "event.h"
#include "queue.h"
//#include "scheduler.h"
//#include "SimEntity.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class Server
{
	public:
		Server ();
		void initialize ();
		void arrivalHandler ();
		void departureHandler ();

		void createTraceFile ();

		inline int& status () { return (status_); }
		inline int& itemArrived () { return (itemArrived_); }
		inline double& arrivalMean () { return (arrivalMean_); }
		inline double& departureMean () { return (departureMean_); }

		//this things are added for lab 03
		void test(Item* var);
        inline int& serverId () { return (serverId_); }
        void schedule_new_arrival();
        Item* createJob();
        void processJob(Item* var);
        inline double& totalSystemDelay () { return (totalSystemDelay_); }
        inline double& totalQueueingDelay () { return (totalQueueingDelay_); }
        inline int& totalQueueingLength () { return (totalQueueingLength_); }

        //for easy implementation SimEntity is imlemented inside server
        Server* next_;
		Server* prev_;
		void send(Item* temp);
		void recev(Item* temp);

		void updateStat(Item* temp);
		void report();



	private:
		Queue* queue_;
		ArrivalEvent a_;
		DepartureEvent d_;

		int status_;
		int itemArrived_;
		Item* itemInService_;
		ofstream trace_;

		double arrivalMean_;
		double departureMean_;
		double exponential (double mean);

		//this things are added for lab 03
		int serverId_;
		double totalSystemDelay_;
		double totalQueueingDelay_;
		int totalQueueingLength_;
};
#endif





