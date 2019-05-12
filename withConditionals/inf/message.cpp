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

//message::message(message &other)
//{
//	copy(other.get_str().begin(), other.get_str().end(), this -> str.begin());
//}

std::string message::get_str() const {return this -> str;};







