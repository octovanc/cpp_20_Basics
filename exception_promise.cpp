#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <stdexcept>


//exception caused in one thread is passed to another thread.
//cp  utlising set_exception() api of std::promise
void func1(std::future<int> &f)
{

    try{

        int x=f.get();
        printf("sqrt value=%d \n",x);
    
    }

    catch(std::exception &e)
    {
        printf("[exception caught- %s]\n",e.what());
    }
    

}

void func2(std::promise<int> &p)
{
    int x=1;
    std::cout<<"enter value\n";
    std::cin>>x;
    try{
         if(x<0)
         {
            throw std::invalid_argument("x<0");
         }
         p.set_value(std::sqrt(x));

    }
    catch (std::exception &)
    {
        p.set_exception(std::current_exception());

    }

}




int main()
{

std::promise<int> p;
std::future<int> f= p.get_future(); //associating future object to promise object
std::thread  t1(func1,std::ref(f)); 
std::thread t2(func2,std::ref(p)); 

t1.join();
t2.join();

return 0;
}

