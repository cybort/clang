/**
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef REFLEXPR_INT_SEQUENCE_1509260923_HPP
#define REFLEXPR_INT_SEQUENCE_1509260923_HPP

#include <type_traits>
#include <cstdint>

namespace std {

template <typename Int, Int ... I>
struct integer_sequence
{
	typedef integer_sequence _type;
};

template <typename IS, typename I>
struct _int_seq_append;

template <typename Int, Int ... I, Int N>
struct _int_seq_append<integer_sequence<Int, I...>, std::integral_constant<Int, N>>
 : integer_sequence<Int, I..., N>
{ };

template <typename N>
struct _make_int_seq;

template <typename Int>
struct _make_int_seq<std::integral_constant<Int, Int(0)>>
 : integer_sequence<Int>
{ };

template <typename Int, Int N>
struct _make_int_seq<std::integral_constant<Int, N>>
 : _int_seq_append<
	typename _make_int_seq<std::integral_constant<Int, N-1>>::_type,
	std::integral_constant<Int, N-1>
>
{ };

template <typename Int, Int N>
using make_integer_sequence =
typename _make_int_seq<std::integral_constant<Int, N>>::_type;


template <std::size_t ... I>
using index_sequence = integer_sequence<std::size_t, I...>;

template <std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

template <typename ... T>
using index_sequence_for = make_index_sequence<sizeof ... (T)>;

} // namespace std

#endif // include guard
