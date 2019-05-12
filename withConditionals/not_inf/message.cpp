#include "message.hpp"


#include <vector>
#include <string>
#include <iostream>    
#include <cstring> 
#include <memory>
#include <mutex>
//#include <condition_variable>




message::message(std::string other_str)
{
	this -> str = other_str;
}

std::string message::get_str() const {return this -> str;};







