#include "iterable_tuple.hpp"

#include <algorithm>
#include <string>

template <typename T>
T clamp(const T& value, const T& min, const T& max) {
    return std::min(std::max(value, min), max);
}

template <typename T>
class Parameter {
  public:
    using value_type = T;
    using const_reference = const value_type&;

    Parameter(const std::string& name, const_reference min, const_reference max, const_reference default_value)
        : name(name), min(min), max(max), default_value(default_value), value(default_value) {}

    value_type& operator=(const_reference value) {
        this->value = clamp(value, min, max);
        return this->value;
    }

    const std::string name;
    const value_type min;
    const value_type max;
    const value_type default_value;

    value_type value;
};

template <>
class Parameter<std::string> {
  public:
    using value_type = std::string;
    using const_reference = const value_type&;

    Parameter(const std::string& name, const_reference default_value)
        : name(name), default_value(default_value), value(default_value) {}

    value_type& operator=(const_reference value) {
        this->value = value;
        return this->value;
    }

    const std::string name;
    const value_type default_value;

    value_type value;
};

template <typename... Ts>
class ParameterList : public iterable_tuple<Parameter<Ts>...> {
  public:
    using iterator = typename iterable_tuple<Parameter<Ts>...>::iterator;
    using const_iterator = typename iterable_tuple<Parameter<Ts>...>::const_iterator;

    ParameterList(Parameter<Ts>&&... data) : iterable_tuple<Parameter<Ts>...>{std::forward<Parameter<Ts>>(data)...} {}

    iterator find(const std::string& name) {
        return std::find_if(this->begin(), this->end(), [&name](auto& parameter) {
            return std::visit([&name](const auto& p) { return p.name == name; }, parameter);
        });
    }

    const_iterator find(const std::string& name) const {
        return std::find_if(this->cbegin(), this->cend(), [&name](auto& parameter) {
            return std::visit([&name](const auto& p) { return p.name == name; }, parameter);
        });
    }
};
