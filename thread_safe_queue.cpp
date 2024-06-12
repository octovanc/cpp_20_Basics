#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
template <typename T>
class thread_safe_queue
{
    private:
     std::mutex m;
     std::queue<std::shared_ptr<T> > q;
     std::condition_variable cv;
     
    public:
    thread_safe_queue();
    thread_safe_queue(thread_safe_queue const& another_queue);


    void push(T &value)
    {
       std::lock_guard<std::mutex> lg(m);
       q.push(std::make_shared<T>(value));
       cv.notify_one();
    };

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lg(m);
        if(q.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> ref(q.front());
        q.pop();
        return ref;        

    }
    bool empty()
    {
               std::lock_guard<std::mutex> lg(m);
                return q.empty();
    }


    std::shared_ptr<T> wait_pop()
    {
               std::unique_lock<std::mutex> ul(m);
               cv.wait(ul,[this] {
                 return !q.empty();
                  } );
               std::shared_ptr<T> ref=q.front();
               q.pop();
               return ref;
    }    
};


int main()
{

return 0;
}

