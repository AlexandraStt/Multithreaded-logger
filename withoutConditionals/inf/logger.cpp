#include <vector>
#include <thread>
#include <string>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <chrono>
//#include <condition_variable>
#include <mutex>
#include <queue>
#include "logger.hpp"


logger::logger(int n, std::ostream& o, int max_e):producers(n), out(o), max_elements(max_e), flag(false), flag_empty_space(false){}

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

  

void logger::print_queue()
{
	out << &this -> q;
} 




void logger::producing_inf_queue()
{
	for (int i = 0; i < 100; i++)
	{
		message m(std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())));
		std::this_thread::sleep_for(std::chrono::milliseconds(std::hash<std::thread::id>{}(std::this_thread::get_id())) % 100);
		std::unique_lock<std::mutex> mtx(this -> m);
		this -> push(m);
		this -> flag = true;
	}
	producers.fetch_sub(1);
}


void logger:: writing_into_file_inf_queue()
{
	while (true)
	{
		std::unique_lock<std::mutex> mtx(this -> m);
		while(!flag)
		{
			mtx.unlock();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			mtx.lock();
			
		}
		while (!this -> q.empty())
		{
			out << this -> front().get_str() << " " << std::endl;
			this -> pop();
		}
		
		this -> flag = false;
		if (this -> producers <= 0)
			break;
	}
}




