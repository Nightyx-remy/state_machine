//
// Created by remy on 1/11/23.
//

#ifndef STATE_MACHINE_LINK_H
#define STATE_MACHINE_LINK_H

#include <functional>
#include <utility>

template<typename T>
class state;

template<typename T>
class link {
public:
    std::string m_name;
    state<T>& m_next;
    std::function<bool(T&)> m_check;

    link(std::string name, state<T>& next, std::function<bool(T&)> check) : m_name(std::move(name)), m_next(next), m_check(check) {}

    bool check(T& data) {
        return this->m_check(data);
    }

};


#endif //STATE_MACHINE_LINK_H
