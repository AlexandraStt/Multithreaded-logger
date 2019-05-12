#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H
	
#include <vector>
#include <iostream>    
//#include <cstring> 
#include <memory>
#include <mutex>
#include <string>
//#include <condition_variable>

class message 
{
	private:
		std::string str;
	public:
		explicit message(std::string other_str);
		std::string get_str() const;
		//explicit message(message &other);
		
		//~message();
};

#endif
