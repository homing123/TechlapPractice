#pragma once;

#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

//Claude에서 만든 코드 이해하면서 공부해보자


template<typename... Args>
class Action {
private:
    struct CallbackWrapper {
        std::function<void(Args...)> callback;
        size_t id;

        CallbackWrapper(const std::function<void(Args...)>& cb)
            : callback(cb), id(GenerateId(cb)) {
        }

        // 함수의 고유 ID 생성 (간단한 해시 방식)
        static size_t GenerateId(const std::function<void(Args...)>& func) {
            // 함수 포인터인 경우
            if (auto ptr = func.template target<void(*)(Args...)>()) {
                return reinterpret_cast<size_t>(*ptr);
            }
            // 그 외의 경우 (람다, 함수 객체 등)
            return reinterpret_cast<size_t>(&func);
        }
    };

    std::vector<CallbackWrapper> callbacks;

public:
    // += 연산자 오버로딩 (함수 추가)
    Action& operator+=(const std::function<void(Args...)>& func) {
        callbacks.emplace_back(func);
        return *this;
    }

    // -= 연산자 오버로딩 (함수 제거)
    Action& operator-=(const std::function<void(Args...)>& func) {
        size_t targetId = CallbackWrapper::GenerateId(func);
        callbacks.erase(
            std::remove_if(callbacks.begin(), callbacks.end(),
                [targetId](const CallbackWrapper& wrapper) {
                    return wrapper.id == targetId;
                }),
            callbacks.end()
        );
        return *this;
    }

    // Invoke 함수 (모든 등록된 함수 호출)
    void Invoke(Args... args) const {
        for (const auto& wrapper : callbacks) {
            if (wrapper.callback) {
                wrapper.callback(args...);
            }
        }
    }

    // () 연산자 오버로딩 (Invoke와 동일)
    void operator()(Args... args) const {
        Invoke(args...);
    }

    // 등록된 함수 개수 반환
    size_t Size() const {
        return callbacks.size();
    }

    // 모든 함수 제거
    void Clear() {
        callbacks.clear();
    }

    // 비어있는지 확인
    bool Empty() const {
        return callbacks.empty();
    }
};