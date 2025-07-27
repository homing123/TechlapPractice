#pragma once;

#include <functional>
#include <vector>
#include <algorithm>
#include <iostream>

//Claude���� ���� �ڵ� �����ϸ鼭 �����غ���


template<typename... Args>
class Action {
private:
    struct CallbackWrapper {
        std::function<void(Args...)> callback;
        size_t id;

        CallbackWrapper(const std::function<void(Args...)>& cb)
            : callback(cb), id(GenerateId(cb)) {
        }

        // �Լ��� ���� ID ���� (������ �ؽ� ���)
        static size_t GenerateId(const std::function<void(Args...)>& func) {
            // �Լ� �������� ���
            if (auto ptr = func.template target<void(*)(Args...)>()) {
                return reinterpret_cast<size_t>(*ptr);
            }
            // �� ���� ��� (����, �Լ� ��ü ��)
            return reinterpret_cast<size_t>(&func);
        }
    };

    std::vector<CallbackWrapper> callbacks;

public:
    // += ������ �����ε� (�Լ� �߰�)
    Action& operator+=(const std::function<void(Args...)>& func) {
        callbacks.emplace_back(func);
        return *this;
    }

    // -= ������ �����ε� (�Լ� ����)
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

    // Invoke �Լ� (��� ��ϵ� �Լ� ȣ��)
    void Invoke(Args... args) const {
        for (const auto& wrapper : callbacks) {
            if (wrapper.callback) {
                wrapper.callback(args...);
            }
        }
    }

    // () ������ �����ε� (Invoke�� ����)
    void operator()(Args... args) const {
        Invoke(args...);
    }

    // ��ϵ� �Լ� ���� ��ȯ
    size_t Size() const {
        return callbacks.size();
    }

    // ��� �Լ� ����
    void Clear() {
        callbacks.clear();
    }

    // ����ִ��� Ȯ��
    bool Empty() const {
        return callbacks.empty();
    }
};