#include <array>
#include <variant>
#include <boost/mp11.hpp>

using boost::mp11::mp_unique;

template <typename... Ts>
class iterable_tuple {
  public:
    using value_type = std::variant<Ts...>;
    using array_type = std::array<mp_unique<value_type>, std::variant_size<value_type>::value>;

    using reference = value_type&;
    using const_reference = const value_type&;

    using iterator = typename array_type::iterator;
    using const_iterator = typename array_type::const_iterator;

    iterable_tuple(Ts&&... data) : data{std::forward<Ts>(data)...} {}

    template <size_t N>
    inline auto& get() {
        return std::get<typename std::variant_alternative<N, value_type>::type>(std::get<N>(data));
    }

    template <size_t N>
    inline const auto& get() const {
        return std::get<typename std::variant_alternative<N, value_type>::type>(std::get<N>(data));
    }

    inline reference at(const size_t n) {
        return data.at(n);
    }

    inline const_reference at(const size_t n) const {
        return data.at(n);
    }

    inline iterator begin() {
        return data.begin();
    }

    inline iterator end() {
        return data.end();
    }

    inline const_iterator begin() const {
        return data.cbegin();
    }

    inline const_iterator end() const {
        return data.cend();
    }

    inline const_iterator cbegin() const {
        return data.cbegin();
    }

    inline const_iterator cend() const {
        return data.cend();
    }

  private:
    array_type data;
};
