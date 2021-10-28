#ifndef queue_h
#define queue_h

typedef struct ItemType {
	int id_;
	ItemType *next_;

	//this two variables are included extra
	int server_id;
	double start_time;
	double queue_exit;
	double start_time2;
	double queue_exit2;
} Item;


class Queue
{
	public:
		Queue ();
		inline int& length () { return (length_); }
		void enque (Item *im);
		Item* deque ();

	private:
		int length_;
		Item *head_;
		Item *tail_;
};

#endif






