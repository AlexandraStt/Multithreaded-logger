#pragma once

#ifndef LOGGER_H
#define LOGGER_H
	
#include "message.hpp"

#include <vector>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>


class logger
{
	private:
		mutable std::mutex m;
		mutable std::condition_variable data_cond;
		std::queue<message> q;
		std::ostream& out;
		std::atomic<int> producers; 
		
	public:
		logger(int n, std::ostream &o);
		void push(message msg);
		void pop();
		message front();
		int size() const;
		void lock() const;
		void print_queue();
		void unlock() const;
		void notify_one();
		void writing_into_file();
		void producing();	
		friend std::ostream& operator<<(std::ostream& os, std::queue<message*> &q_print);
};






#endif
