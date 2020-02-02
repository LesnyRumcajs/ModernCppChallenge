#pragma once

#include <utility>
#include <vector>
#include <memory>
#include <functional>

namespace cppchallenge::design_patterns {
    enum class CollectionAction {
        add,
        assign,
        remove,
        clear
    };

    struct CollectionChangeNotification {
        CollectionAction action;

        CollectionChangeNotification(CollectionAction action, std::vector<size_t> changed_indeces = {}) : action(
                action), changed_indeces(std::move(changed_indeces)) {}

        std::vector<size_t> changed_indeces;

        bool operator==(const CollectionChangeNotification &rhs) const {
            return action == rhs.action &&
                   changed_indeces == rhs.changed_indeces;
        }

        bool operator!=(const CollectionChangeNotification &rhs) const {
            return !(rhs == *this);
        }
    };

    class CollectionObserver {
    public:
        virtual void changed(const CollectionChangeNotification& notification) = 0;

        virtual ~CollectionObserver() = default;
    };

    class Observer : public CollectionObserver {
    public:
        void changed(const CollectionChangeNotification &notification) override {
            notifications.push_back(notification);
        }

        [[nodiscard]] const std::vector<CollectionChangeNotification>& get_notifications() const {
            return notifications;
        }

    private:
        std::vector<CollectionChangeNotification> notifications;
    };

    template <typename T, class Allocator = std::allocator<T>>
    class ObservedVector final {
        using size_type = typename std::vector<T, Allocator>::size_type;

    public:
        ObservedVector() noexcept(noexcept(Allocator())) : ObservedVector(Allocator()) {}
        ObservedVector(const ObservedVector& other, const Allocator& allocator = Allocator()) : data(other.data, allocator) {}
        explicit ObservedVector(const Allocator& allocator) noexcept : data(allocator) {}
        ObservedVector(size_type size, const T& value, const Allocator& allocator = Allocator())
            : data(size, value, allocator) {}

        ObservedVector(size_type size, const Allocator& allocator) : data(size, allocator) {}

        ObservedVector(ObservedVector&& other) noexcept : data(other.data) { other.data.clear(); }
        ObservedVector(ObservedVector&& other, const Allocator& allocator) : data(other.data, allocator)
            { other.data.clear(); }

        ObservedVector(std::initializer_list<T> list, const Allocator& allocator = Allocator())
            : data(list, allocator) {}

        template<typename Iterator>
        ObservedVector(Iterator begin, Iterator end, const Allocator& allocator = Allocator())
            : data(begin, end, allocator) {}

        void notify_observers(CollectionChangeNotification notification) {
            for (const auto& observer : observers) {
                if (auto observe = observer.lock()) {
                    observe->changed(notification);
                }
            }
        }

        ObservedVector& operator=(const ObservedVector& rhs) {
            if (this != &rhs) {
                data = rhs.data;
                notify_observers({CollectionAction::assign});
            }

            return *this;
        }

        void push_back(T&& value) {
            data.push_back(value);
            notify_observers({CollectionAction::add, {data.size() - 1}});
        }

        void pop_back() {
            data.pop_back();
            notify_observers({CollectionAction::remove, {data.size()}});
        }

        void clear() noexcept {
            data.clear();
            notify_observers({CollectionAction::clear});
        }

        [[nodiscard]] size_type size() const noexcept {
            return data.size();
        }

        [[nodiscard]] bool empty() const noexcept {
            return data.empty();
        }

        void add_observer(const std::shared_ptr<CollectionObserver>& to_add) {
            auto already_exists = std::any_of(observers.begin(), observers.end(), [&to_add](const auto& observer) {
                return observer.lock() == to_add;
            });

            if (!already_exists) {
                observers.push_back(to_add);
            }
        }

        void remove_observer(const std::shared_ptr<CollectionObserver>& to_remove) {
            observers.erase(std::remove_if(observers.begin(), observers.end(), [&to_remove](const auto& observer) {
                return observer.lock() == to_remove;
            }));
        }

        bool operator==(const ObservedVector &rhs) const {
            return data == rhs.data;
        }

        bool operator!=(const ObservedVector &rhs) const {
            return !(rhs == *this);
        }

    private:
        std::vector<T, Allocator> data;
        std::vector<std::weak_ptr<CollectionObserver>> observers;
    };
}