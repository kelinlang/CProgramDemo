#pragma once
#include<vector>
#include<queue>
#include<memory>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<stdexcept>

class ThreadPool
{
public:
	ThreadPool(size_t);
	template<typename F,typename...Args>
	auto enqueue(F&& f, Args&&...args)
		-> std::future<typename std::result_of<F(Args...)>::type>;
	~ThreadPool();

private:
	std::vector<std::thread> workers;
	std::queue < std::function<void()> > tasks;

	std::mutex queue_mutex;
	std::condition_variable condition;

	bool stop;

};



inline ThreadPool::ThreadPool(size_t threads) : stop(false)
{
	for (size_t i = 0; i < threads; i++)
	{
		workers.emplace_back(std::thread([this] 
			{
				for (;;) {//线程的loop
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(this->queue_mutex);
						condition.wait(lock, [this] {return stop || !tasks.empty(); });
						if (stop && tasks.empty())
							return;//两个条件满足，返回结束线程
						task = std::move(tasks.front());
						tasks.pop();
					}
					task();
				}
			}));
	}
}

inline ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (auto& worker : workers) {
		worker.join();
	}
}

template<typename F, typename ...Args>
inline auto ThreadPool::enqueue(F&& f, Args&& ...args) -> std::future<typename std::result_of<F(Args ...)>::type>
{
	using return_type = typename std::result_of<F(Args ...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...) //bind返回了function
		);

	std::future<return_type> res = task->get_future();//访问智能指针get方法返回对象的原始指针，->可以直接访问对象的public方法
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		if (stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}
		//std::queue < std::function<void()> > tasks;
		tasks.emplace([task]() {//task是智能指针，*task 就是放在其中的packaged_task
			(*task)();//这个task再包装成一个std::function放入taskQueue中
			});
	}
	condition.notify_one();

	return res;
}
