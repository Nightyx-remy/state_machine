//
// Created by remy on 1/17/23.
//

#ifndef STATE_MACHINE_STATE_MACHINE_BUILDER_H
#define STATE_MACHINE_STATE_MACHINE_BUILDER_H

#include "state_machine.h"
#include "state.h"
#include "link.h"

template<typename T>
class state_machine_builder {
public:
    state_machine_builder() = default;

    state_machine<T> build() {
        return machine;
    }

    state_machine_builder<T>& add_state(std::string name, std::function<void()> behavior) {
        machine.states.template emplace_back(name, behavior);
        return *this;
    }

    state_machine_builder<T>& link_states(const std::string& from, const std::string& to, std::string name, std::function<bool(T&)> check) {
        state<T>* from_state = nullptr;

        for (state<T>& state : machine.states) {
            if (state.m_name == from) {
                from_state = &state;
                break;
            }
        }
        if (from_state == nullptr) {
            std::cout << "Error: Failed to find state '" << from << "'!" << std::endl;
            return *this;
        }

        state<T>* to_state = nullptr;
        for (state<T>& state : machine.states) {
            if (state.m_name == to) {
                to_state = &state;
                break;
            }
        }
        if (to_state == nullptr) {
            std::cout << "Error: Failed to find state '" << to << "'!" << std::endl;
            return *this;
        }

        from_state->links.emplace_back(name, *to_state, check);

        return *this;
    }
private:
    state_machine<T> machine;
};

#endif //STATE_MACHINE_STATE_MACHINE_BUILDER_H
