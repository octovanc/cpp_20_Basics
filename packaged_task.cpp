#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <stdexcept>


int add(int x,int y)
{
    std::cout<<"thread-Id:"<<std::this_thread::get_id()<<std::endl;
    return x+y;
}
//t1 runs asynchronously
void task_async()
{
std::packaged_task<int(int,int)> p1(add);
std::future<int> f(p1.get_future());

std::thread t1(std::move(p1),4,5); //packaged_task isnt movable
std::cout<<"async->"<<f.get()<<std::endl;
t1.detach();


}

void task_normal()
{
    std::packaged_task<int(int,int)> p1(add);
std::future<int> f(p1.get_future());
p1(5,6);
std::cout<<"main_thread->"<<f.get()<<std::endl;

}
int main()
{
    task_normal(); //runs in main thread;
    task_async();
    std::cout<<"thread-Id_main:"<<std::this_thread::get_id()<<std::endl;


return 0;
}

