#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>




void func(std::future<int> &f)
{
    printf("waiting for value from print thread\n");
    std::cout<<"value recieved at print thread-"<<f.get()<<std::endl; // will wait until value set by promise.
}


int main()
{

std::promise<int> p;
std::future<int> f= p.get_future(); //associating future object to promise object
std::thread  t1(func,std::ref(f)); //spawing print thread and passing future object reference as argument
std::this_thread::sleep_for(std::chrono::milliseconds(5000));
printf("setting value in main thread\n");
p.set_value(10); //setting value to future.
t1.join();

return 0;
}

