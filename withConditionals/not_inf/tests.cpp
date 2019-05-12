#include <valgrind/drd.h>
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_BEFORE(addr) ANNOTATE_HAPPENS_BEFORE(addr)
#define _GLIBCXX_SYNCHRONIZATION_HAPPENS_AFTER(addr)  ANNOTATE_HAPPENS_AFTER(addr)


#include <gtest/gtest.h>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <typeinfo>


#include "logger.hpp"


/*
TEST(TestLogger, TestQueue1)
{
	int n = 5;
	std::ofstream out("check_logger1.txt");
	logger lg(n, std::ref(out), 100);
	
	std::vector<std::thread> threads(n);

	std::thread consumer_thread(&logger::writing_into_file, &lg);
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&logger::producing, &lg);
	
	for (int i = 0; i < n; i++)
		threads[i].join();
	consumer_thread.join();
}
*/
TEST(TestLogger, TestQueue2)
{
	int n = 10;
	
	std::ofstream out("check_logger2.txt");
	logger lg(n, std::ref(out), 100);
	
	std::vector<std::thread> threads(n);

	std::thread consumer_thread(&logger::writing_into_file, &lg);
	for (int i = 0; i < n; i++)
		threads[i] = std::thread(&logger::producing, &lg);
	
	for (int i = 0; i < n; i++)
		threads[i].join();
	consumer_thread.join();
}


int main(int argc, char **argv)
{
	
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();	
}
