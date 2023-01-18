#include <iostream>

#include "state_machine.h"
#include "state_machine_builder.h"
#include "state.h"
#include "link.h"

int main() {
    std::string str = "2.14";

    state_machine_builder<char> builder{};
    state_machine<char> machine = builder
            .add_state("int", []() {})
            .add_state("double", []() {})
            .add_state("error", []() {
                std::cout << "Error" << std::endl;
            })
            .link_states("int", "int", "digit", [](char c) {
                return isdigit(c);
            })
            .link_states("int", "double", "dot", [](char c) {
                return c == '.';
            })
            .link_states("int", "error", "else", [](char c) {
                return true;
            })
            .link_states("double", "double", "digit", [](char c) {
                return isdigit(c);
            })
            .link_states("double", "error", "else", [](char c) {
                return true;
            })
            .build();

    for (char c : str) {
        if (!machine.execute(c)) break;
    }

    auto s = machine.generate_graph();
    std::cout << s << std::endl;

    return 0;
}
