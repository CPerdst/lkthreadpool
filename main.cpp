#include <iostream>

#include "IThreadPool.h"
#include "ThreadPool.h"
#include "mutex"
#include "eventCapturer.h"

int main() {
    // 设置日志登记
    logger::logger::Root()->setLevel(packer::Debug);
    // 设置日志格式
    logger::logger::Root()->setLogFormater("[%filepath:%line]: %message\n");
    // 设置日志输出到对应的文件
    // logger::logger::Root()->logToFile("./test.txt");
    IThreadPool* t = new ThreadPool(3, 10, 10000);
    std::mutex mtx;
    int count = 0;
    t->start();
    for(int i = 0; i < 10000; i++){
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
