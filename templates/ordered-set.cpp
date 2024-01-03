#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename Type, typename ComparatorFn = less<Type>>
using oset = tree<Type, null_type, ComparatorFn, rb_tree_tag, tree_order_statistics_node_update>;

// methods -> *find_by_order, order_of_key
// comparators -> less, less_equal, greater, greater_equal