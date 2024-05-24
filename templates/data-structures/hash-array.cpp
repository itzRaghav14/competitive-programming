template<typename... Ts, size_t... Is, typename F>
void __op(index_sequence<Is...>, tuple<Ts...>& a, const tuple<Ts...>& b, F op) { ((get<Is>(a) = op(get<Is>(a), get<Is>(b))), ...); }
#define OVERLOAD(OP, F) \
template<typename... Ts> auto& operator OP##=(tuple<Ts...> &a, const tuple<Ts...> &b) { __op(index_sequence_for<Ts...>(), a, b, F<>{}); return a; } \
template<typename... Ts> auto operator OP(const tuple<Ts...> &a, const tuple<Ts...> &b) { auto c = a; c OP##= b; return c; }
OVERLOAD(+, plus) OVERLOAD(-, minus) OVERLOAD(*, multiplies) OVERLOAD(/, divides)

constexpr int NUM_HASHES = 2; // *
constexpr array<int, NUM_HASHES> mods = {127657753, 987654319}; // *
template <size_t N = NUM_HASHES> constexpr auto mint_ntuple(const int &v) { return [&]<size_t... Is>(index_sequence<Is...>) { return make_tuple(mint<mods[Is]>(v)...); }(make_index_sequence<N>{}); }

using HT = decltype(mint_ntuple(0)); 
HT hash0 = mint_ntuple(0);