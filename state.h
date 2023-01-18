//
// Created by remy on 1/11/23.
//

#ifndef STATE_MACHINE_STATE_H
#define STATE_MACHINE_STATE_H

#include <utility>
#include <vector>
#include <functional>
#include "link.h"

template<typename T>
class state {
public:
    std::string m_name;
    std::vector<link<T>> links{};
    std::function<void()> m_behavior;

    state(std::string name, std::function<void()> behavior) : m_name(std::move(name)), m_behavior(std::move(behavior)) {}

    void execute() {
        this->m_behavior();
    }
};


#endif //STATE_MACHINE_STATE_H
