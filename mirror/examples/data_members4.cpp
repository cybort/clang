#include "reflexpr.hpp"
#include <iostream>

template <typename T>
std::ostream& value_to_json(std::ostream& out, const T& v);

template <typename ... T>
void eat(T ... ) { }

template <typename Metaobjects, std::size_t I, typename T>
int field_to_json(std::ostream& out, const T& v)
{
	typedef std::meta::get_element_t<Metaobjects, I> meta_F;

	if(I > 0) out << ", ";

	out << '"' << std::meta::get_name_v<meta_F> << "\": ";

	value_to_json(out, (v.*std::meta::get_pointer<meta_F>::value));

	return 0;
}

template <typename Metaobjects, std::size_t ... I, typename T>
void fields_to_json(std::ostream& out, const T& v, std::index_sequence<I...>)
{
	eat(field_to_json<Metaobjects, I>(out, v)...);
}

template <typename MO, typename T>
std::ostream& reflected_to_json(std::ostream& out, const T& v, std::true_type)
{
	out << "{";

	typedef std::meta::get_all_data_members_t<MO> meta_DMs;
	fields_to_json<meta_DMs>(
		out, v,
		std::make_index_sequence<
			std::meta::get_size_v<meta_DMs>
		>()
	);

	out << "}";
	return out;
}

template <typename MO, typename T>
std::ostream& reflected_to_json(std::ostream& out, const T& v, std::false_type)
{
	return out << v;
}

template <typename T>
std::ostream& value_to_json(std::ostream& out, const T& v)
{
	typedef reflexpr(T) meta_T;
	return reflected_to_json<meta_T>(
		out, v,
		std::meta::is_class_t<meta_T>()
	);
};

struct point
{
	float x, y, z;
};

struct triangle
{
	point a, b, c;
};

struct tetrahedron
{
	triangle base;
	point apex;
};

int main(void)
{
	using namespace std;

	tetrahedron t{
		{
			{0.f,0.f,0.f},
			{1.f,0.f,0.f},
			{0.f,0.f,1.f}
		}, {0.f,1.f,0.f}
	};

	std::cout << "{\"t\": ";
	value_to_json(std::cout, t);
	std::cout << "}"  << std::endl;

	return 0;
}
