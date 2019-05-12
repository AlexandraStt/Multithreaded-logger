#include <vector>
#include <thread>
#include <string>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>
#include "logger.hpp"


logger::logger(int n, std::ostream& o):producers(n), out(o){}

void logger::push(message msg)
{
	this -> q.push(msg);
}

void logger::pop()
{
	this -> q.pop();
}

message logger::front()
{
	return q.front();
}


int logger::size() const
{
	return this -> q.size();
}


void logger::notify_one()
{
	this -> data_cond.notify_one();
}
      

/*
std::ostream& operator<<(std::ostream& os, std::queue<message*> &q_print)
{
	out << "kek" << std::endl;
	while (!q_print.empty())
	{
		out << q_print.front() -> get_str() << " ";
		out << std::endl;
		q_print.pop();
	}
		//std::cout << (*i) << "  ";
	out << std::endl;
	return os;
}
*/

void logger::print_queue()
{
	out << &this -> q;
} 



void logger::producing()
{
	for (int i = 0; i < 10; i++)
	{
		message m(std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())));
		std::lock_guard<std::mutex> mtx(this -> m);
		this -> push(m);
		this -> notify_one();
	}
	producers.fetch_sub(1);
}


void logger:: writing_into_file()
{
	while (this -> producers > 0 || !this -> q.empty())
	{
		std::unique_lock<std::mutex> mtx(this -> m);
		this -> data_cond.wait(mtx, [&](){return !(this -> q).empty();});
		out << this -> front().get_str() << " " << std::endl;
		this -> pop();
	}
}




