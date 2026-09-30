#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <condition_variable>
#include <chrono>

class TaskQueue {
public:
    void push(int task) {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(task);
        cv.notify_one();
    }

    bool pop(int& task) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !tasks.empty() || stop_flag; });
        
        if (tasks.empty() && stop_flag) {
            return false;
        }

        task = tasks.front();
        tasks.pop();
        return true;
    }

    void shutdown() {
        std::unique_lock<std::mutex> lock(mtx);
        stop_flag = true;
        cv.notify_all();
    }

private:
    std::queue<int> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop_flag = false;
};

std::mutex cout_mtx;

void worker_func(int id, TaskQueue& queue) {
    int task;
    while (queue.pop(task)) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "[Worker-" << id << "] обработал задачу " << task << std::endl;
    }
}

int main() {
    system("chcp 65001 > nul");

    TaskQueue queue;
    int num_workers = 4;
    std::vector<std::thread> workers;

    for (int i = 1; i <= num_workers; ++i) {
        workers.push_back(std::thread(worker_func, i, std::ref(queue)));
    }

    for (int i = 1; i <= 20; ++i) {
        queue.push(i);
    }

    queue.shutdown();

    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    return 0;
}