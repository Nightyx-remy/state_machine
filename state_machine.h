//
// Created by remy on 1/11/23.
//

#ifndef STATE_MACHINE_STATE_MACHINE_H
#define STATE_MACHINE_STATE_MACHINE_H

#include <utility>
#include <vector>
#include "state.h"
#include <functional>

template<typename T>
class state_machine {
public:
    std::vector<state<T>> states{};
    state<T>* current = nullptr;

    state_machine() = default;

    bool execute(T input) {
        if (current == nullptr) {
            current = &states.front();
            current->execute();
        }

        if (current->links.empty()) {
            current = nullptr;
            return false;
        }

        for (link<T> link : current->links) {
            if (link.check(input)) {
                current = &link.m_next;
                current->execute();
                return true;
            }
        }
        return false;
    }

    std::string generate_graph() {
        auto buf = std::string();

        buf.append("stateDiagram-v2\n");

        for (state<T> state : this->states) {
            for (link<T> link : state.links) {
                buf.append("\t");
                buf.append(state.m_name);
                buf.append(" --> ");
                buf.append(link.m_next.m_name);
                buf.append(": ");
                buf.append(link.m_name);
                buf.append("\n");
            }
        }

        return buf;
    }

};


#endif //STATE_MACHINE_STATE_MACHINE_H
