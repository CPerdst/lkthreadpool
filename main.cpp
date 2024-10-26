#include <iostream>

#include "IThreadPool.h"
#include "ThreadPool.h"
#include "mutex"

int main() {
    std::cout << "Hello, World!" << std::endl;
    IThreadPool* t = new ThreadPool(3, 10, 10000);
    std::mutex mtx;
    int count = 0;
    t->start();
    for(int i = 0; i < 1; i++){
        t->add_task([&](){
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << count++ << std::endl;
        });
    }

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
