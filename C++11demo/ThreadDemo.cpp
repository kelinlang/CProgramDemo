#include "ThreadDemo.h"

void testThread()
{
	std::thread t([]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(900));
		std::cout << "hello world." << std::endl;
		});
	t.join();
}
