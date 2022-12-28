
#include <condition_variable>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <omp.h>
#include <queue>
#include <set>

const int PROD_NUMS = 6;
const int CONS_NUMS = 4;
const int maxN = 100;

template <class T, class Container = std::queue<T>>
class ThreadSafeQueue {

private:
    Container _queue;
    std::condition_variable _not_empty_cv;
    mutable std::mutex _mutex;

public:
    ThreadSafeQueue() {};

    template <class Element>
    void push(Element&& element)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _queue.push(std::forward<Element>(element));
        _not_empty_cv.notify_one();
    }

    void waitAndPop(T& t)
    {
        std::unique_lock<std::mutex> lock(_mutex);
        _not_empty_cv.wait(
            lock, [this] {
                return !_queue.empty();
            });

        t = std::move(_queue.front());
        _queue.pop();
    }

    bool isEmpty() const
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.empty();
    }

    int size()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        return _queue.size();
    }
};

// parameter to save key and count keys
std::set<std::string> keys;
std::map<std::string, int> keys_cnt;

// queue use to store words
ThreadSafeQueue<std::string> queue;

void execute()
{
#pragma omp parallel num_threads(PROD_NUMS)
    {
        int id = omp_get_thread_num();
        std::string str;
        std::ifstream prod_ifs("words/" + std::to_string(id) + ".txt", std::ios::in);
        while (std::getline(prod_ifs, str, ' '))
            queue.push(str);
    }

    int size = queue.size();
#pragma omp parallel for num_threads(CONS_NUMS)
    for (int i = 1; i <= size; i++) {
        std::string str;
        queue.waitAndPop(str);
        if (keys.find(str) != keys.end()) {
#pragma omp atomic
            keys_cnt[str] += 1;
        }
    }
}

int main()
{
    // read keyword from file
    std::string str;
    std::ifstream keys_ifs("words/keys.txt", std::ios::in);
    if (!keys_ifs.is_open()) {
        std::cout << "Failed to open keywords file\n";
        return 1;
    }
    while (std::getline(keys_ifs, str)) {
        keys.insert(str);
        keys_cnt[str] = 0;
    }

    // produce and consume
    omp_set_num_threads(PROD_NUMS + CONS_NUMS);
    execute();

    for (auto it : keys_cnt) {
        std::cout << it.first << ' ' << it.second << '\n';
    }
}
