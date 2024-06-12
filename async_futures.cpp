#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>



void print()
{
    std::cout<<std::this_thread::get_id()<<"-print_id\n";

printf("print fn\n");
}
int add(int x,int y)
{
        std::cout<<std::this_thread::get_id()<<"-add_id\n";

    return x+y;
}
int subtract(int x,int y)
{
        std::cout<<std::this_thread::get_id()<<"-subtract_id\n";

    return x-y;
}

int main()
{
    int x,y;
x=4;
y=10;
std::cout<<std::this_thread::get_id()<<"-main_id\n";
std::future<void> f1=std::async(std::launch::async,print);
std::future<int> f2= std::async(std::launch::deferred,add,x,y);
std::future<int> f3= std::async(std::launch::deferred,subtract,x,y);

f1.get();
std::cout<<"async-add "<<f2.get()<<std::endl;
std::cout<<"async-subtract "<<f3.get()<<std::endl;


return 0;
}

