//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_SERIALIZATION_LOAD_VARIANT_HPP_INCLUDED
#define ALDA_SERIALIZATION_LOAD_VARIANT_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <alda/bindings/invalid_variant.hpp>
#include <alda/bindings/variant_decl.hpp>
#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/load_variant.hpp>
#include <alda/serialization/load/fwd.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/io/read.hpp>
#include <fcppt/mpl/invoke_on.hpp>


namespace alda
{
namespace serialization
{

template<
	typename Types,
	typename AdaptedTypes
>
struct load<
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>
>
{
	static
	typename
	alda::bindings::variant<
		Types,
		AdaptedTypes
	>::type
	get(
		alda::serialization::istream &_is
	)
	{
		typedef
		alda::bindings::variant<
			Types,
			AdaptedTypes
		> type;

		return
			fcppt::mpl::invoke_on<
				Types
			>(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					fcppt::io::read<
						typename type::index_type::type
					>(
						_is,
						alda::endianness()
					)
				),
				alda::serialization::detail::load_variant<
					Types,
					AdaptedTypes
				>(
					_is
				),
				[]()
				->
				typename
				alda::bindings::variant<
					Types,
					AdaptedTypes
				>::type
				{
					throw
						alda::bindings::invalid_variant();
				}
			);
	}
};

}
}

#endif
