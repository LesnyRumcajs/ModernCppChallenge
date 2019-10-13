#pragma once

#include <atomic>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "sync_log.h"

namespace cppchallenge::concurrency {
    class TicketMachine {
    public:
        unsigned generate_ticket() {
            return ++ticket_count;
        }

        [[nodiscard]]
        unsigned count() const {
            return ticket_count;
        }
    private:
        std::atomic<unsigned> ticket_count = 0;
    };

    class Customer {
    public:
        explicit Customer(unsigned ticket_number, std::chrono::milliseconds work_amount = std::chrono::milliseconds(1)) :
            ticket_number(ticket_number),
            work_amount(work_amount) {}

        [[nodiscard]]
        auto get_ticket_number() const noexcept {
            return ticket_number;
        }

        [[nodiscard]]
        auto get_work_amount() const noexcept {
            return work_amount;
        }
    private:
        unsigned ticket_number;
        std::chrono::milliseconds work_amount;

        friend bool operator<(const Customer& lhs, const Customer& rhs) noexcept ;
    };

    bool operator<(const Customer& lhs, const Customer& rhs) noexcept {
        return lhs.ticket_number > rhs.ticket_number;
    }

    class Office {
    public:
        Office() = default;

        ~Office() {
            close();
        }

        void open(unsigned workers_count) {
            if (office_open) {
                throw std::runtime_error("Already opened!");
            }

            logger.log("Opening office");
            using namespace std::chrono_literals;

            for (auto id(1u); id <= workers_count; ++id) {
                workers.emplace_back([id, this]() {
                    logger.log("Worker " + std::to_string(id) + " available");
                    while (office_open || !customers.empty()) {
                        std::unique_lock lock(mt);
                        cv.wait_for(lock, 1s, [this]() {
                            return !customers.empty();
                        });

                        if (!customers.empty()) {
                            const auto customer = customers.top();
                            customers.pop();

                            lock.unlock();
                            cv.notify_one();

                            logger.log("Worker " + std::to_string(id) +
                                       " handling customer " + std::to_string(customer.get_ticket_number()));
                            std::this_thread::sleep_for(customer.get_work_amount());
                        }
                    }
                });
            }

            office_open = true;
            logger.log("Office opened");
        }

        void add_customer(std::chrono::milliseconds work_amount) {
            auto customer = Customer(ticketMachine.generate_ticket(), work_amount);
            customers.push(customer);
            cv.notify_one();
        }

        void close() {
            if (office_open) {
                logger.log("Closing office...");
                office_open = false;
                for (auto& worker : workers) {
                    worker.join();
                }
                logger.log("Office closed.");
            }
        }

        [[nodiscard]]
        bool is_office_open() const noexcept {
            return office_open;
        }

        [[nodiscard]]
        auto queue_size() const noexcept {
            return customers.size();
        }

    private:
        TicketMachine ticketMachine;
        SyncLogger logger;

        std::vector<std::thread> workers;

        std::atomic<bool> office_open = false;
        std::mutex mt;
        std::condition_variable cv;
        std::priority_queue<Customer> customers;
    };
}
