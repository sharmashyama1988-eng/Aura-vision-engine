#pragma once

#include "Aura/Core/Base.hpp"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

namespace aura::core {

    class TaskScheduler {
    public:
        TaskScheduler(uint32_t threadCount = std::thread::hardware_concurrency());
        ~TaskScheduler();

        template<class F, class... Args>
        auto Enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result<F, Args...>::type> {
            using return_type = typename std::invoke_result<F, Args...>::type;

            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

            std::future<return_type> res = task->get_future();
            {
                std::unique_lock<std::mutex> lock(m_QueueMutex);
                if (m_Stop) throw std::runtime_error("Enqueue on stopped TaskScheduler");
                m_Tasks.emplace([task]() { (*task)(); });
            }
            m_Condition.notify_one();
            return res;
        }

    private:
        std::vector<std::thread> m_Workers;
        std::queue<std::function<void()>> m_Tasks;

        std::mutex m_QueueMutex;
        std::condition_variable m_Condition;
        bool m_Stop;
    };

} // namespace aura::core
