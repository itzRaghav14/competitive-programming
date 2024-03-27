#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename Type, typename ComparatorFn = less<Type>>
using oset = tree<Type, null_type, ComparatorFn, rb_tree_tag, tree_order_statistics_node_update>;

// template<typename Type, typename ComparatorFn>
// bool oset_erase (oset<Type, ComparatorFn> &st, Type val) {
// 	if (st.lower_bound(val) == st.upper_bound(val)) return false;
// 	st.erase(st.find_by_order(st.order_of_key(val)));
// 	return true;
// }

// methods -> *find_by_order, order_of_key
// comparators -> less, less_equal, greater, greater_equal