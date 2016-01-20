#include "reflexpr.hpp"
#include <iostream>

struct foo
{
private:
	int _i, _j;
public:
	static constexpr const bool b = true;
	float x, y, z;
private:
	static double d;
};

int main(void)
{
	using namespace std;

	typedef reflexpr(foo) meta_foo;

	// (public) data members
	typedef meta::get_data_members_t<meta_foo> meta_data_mems;

	static_assert(is_metaobject_v<meta_data_mems>, "");
	static_assert(meta::is_sequence_v<meta_data_mems>, "");

	cout << meta::get_size_v<meta_data_mems> << endl;

	// 0-th (public) data member
	typedef meta::get_element_t<meta_data_mems, 0> meta_data_mem0;

	static_assert(is_metaobject_v<meta_data_mem0>, "");
	static_assert(meta::is_variable_v<meta_data_mem0>, "");
	static_assert(meta::has_type_v<meta_data_mem0>, "");

	cout << meta::get_name_v<meta_data_mem0> << endl;

	// 2-nd (public) data member
	typedef meta::get_element_t<meta_data_mems, 2> meta_data_mem2;

	static_assert(is_metaobject_v<meta_data_mem2>, "");
	static_assert(meta::is_variable_v<meta_data_mem2>, "");
	static_assert(meta::has_type_v<meta_data_mem2>, "");

	cout << meta::get_name_v<meta_data_mem2> << endl;

	// all data members
	typedef meta::get_all_data_members_t<meta_foo> meta_all_data_mems;

	static_assert(is_metaobject_v<meta_all_data_mems>, "");
	static_assert(meta::is_sequence_v<meta_all_data_mems>, "");

	cout << meta::get_size_v<meta_all_data_mems> << endl;

	// 0-th (overall) data member
	typedef meta::get_element_t<meta_all_data_mems, 0> meta_all_data_mem0;

	static_assert(is_metaobject_v<meta_all_data_mem0>, "");
	static_assert(meta::is_variable_v<meta_all_data_mem0>, "");
	static_assert(meta::has_type_v<meta_all_data_mem0>, "");

	cout << meta::get_name_v<meta_all_data_mem0> << endl;

	// 3-rd (overall) data member
	typedef meta::get_element_t<meta_all_data_mems, 3> meta_all_data_mem3;

	static_assert(is_metaobject_v<meta_all_data_mem3>, "");
	static_assert(meta::is_variable_v<meta_all_data_mem3>, "");
	static_assert(meta::has_type_v<meta_all_data_mem3>, "");

	cout << meta::get_name_v<meta_all_data_mem3> << endl;

	return 0;
}
