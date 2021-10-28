//this class is included just like sir told us to

#ifndef SimEntity_h
#define SimEntity_h

#include "Queue.h";
#include "Server.h"

class SimEntity
{
	public:
		void send(Item* item);
		void recev(Item* item);
		void set_next(Server* var);
		Server* get_next();
		void set_prev(Server* var);
		Server* get_prev();

	private:
		Server *next;
		Server *prev;


};

#endif


