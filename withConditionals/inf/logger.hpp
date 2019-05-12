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
		std::atomic<int> max_elements;
		
	public:
		logger(int n, std::ostream &o, int max_elements = 2000000);
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
		void writing_into_file_inf_queue();
		void producing_inf_queue();	
		friend std::ostream& operator<<(std::ostream& os, std::queue<message*> &q_print);
};






#endif
