#include "parameters.hpp"

#include <iostream>
#include <variant>

static ParameterList parameters{
    Parameter{"param_1", 1, 3, 2},
    Parameter{"param_2", 1.0f, 3.0f, 2.0f},
    Parameter<std::string>{"param_3", "a"},
    Parameter{"param_4", 1, 3, 2},
};

int main() {
    auto& a = parameters.get<0>();
    auto& b = parameters.get<1>();
    auto& c = parameters.get<2>();

    auto p = parameters.find("param_2");
    if (p != parameters.cend()) {
        std::visit([](auto& p) {
            std::cout << p.name << ": " << p.value << std::endl;
        }, *p);
    }

    a = 4;
    b = 4.0f;
    c = "b";

    for (auto& parameter : parameters) {
        std::visit([](auto& p) {
            std::cout << p.name << ": " << p.value << std::endl;
        }, parameter);
    }

    return 0;
}
