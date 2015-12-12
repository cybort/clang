#include "reflexpr.hpp"
#include <iostream>

namespace foo { namespace bar { } }

namespace foobar = foo::bar;

int main(void)
{
	using namespace std;

	// reflected namespace foo
	typedef reflexpr(foo) meta_foo;

	static_assert(is_metaobject_v<meta_foo>, "");

	static_assert(!meta::is_global_scope_v<meta_foo>, "");
	static_assert(meta::is_namespace_v<meta_foo>, "");
	static_assert(!meta::is_type_v<meta_foo>, "");
	static_assert(!meta::is_alias_v<meta_foo>, "");

	static_assert(meta::has_name_v<meta_foo>, "");
	static_assert(meta::has_scope_v<meta_foo>, "");
	cout << meta::get_name_v<meta_foo> << endl;

	// reflected nested namespace foo::bar
	typedef reflexpr(foo::bar) meta_foo_bar;

	static_assert(is_metaobject_v<meta_foo_bar>, "");

	static_assert(!meta::is_global_scope_v<meta_foo_bar>, "");
	static_assert(meta::is_namespace_v<meta_foo_bar>, "");
	static_assert(!meta::is_type_v<meta_foo_bar>, "");
	static_assert(!meta::is_alias_v<meta_foo_bar>, "");

	static_assert(meta::has_name_v<meta_foo_bar>, "");
	static_assert(meta::has_scope_v<meta_foo_bar>, "");
	cout << meta::get_name_v<meta_foo_bar> << endl;

	// reflected namespace alias foobar
	typedef reflexpr(foobar) meta_foobar;

	static_assert(is_metaobject_v<meta_foobar>, "");

	static_assert(!meta::is_global_scope_v<meta_foobar>, "");
	static_assert(meta::is_namespace_v<meta_foobar>, "");
	static_assert(!meta::is_type_v<meta_foobar>, "");
	static_assert(meta::is_alias_v<meta_foobar>, "");

	static_assert(meta::has_name_v<meta_foobar>, "");
	static_assert(meta::has_scope_v<meta_foobar>, "");
	cout << meta::get_name_v<meta_foobar> << " a.k.a ";
	cout << meta::get_name_v<meta::get_aliased_t<meta_foobar>> << endl;

	return 0;
}
