//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ALDA_BINDINGS_RECORD_HPP_INCLUDED
#define ALDA_BINDINGS_RECORD_HPP_INCLUDED

#include <alda/bindings/record_decl.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/detail/extract_length.hpp>
#include <alda/bindings/detail/put_length.hpp>
#include <alda/serialization/detail/read/make_object.hpp>
#include <majutsu/dispatch_type.hpp>
#include <majutsu/raw/const_pointer.hpp>
#include <majutsu/raw/pointer.hpp>
#include <majutsu/raw/size_type.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/array.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type
>
inline
majutsu::raw::size_type
needed_size(
	majutsu::dispatch_type<
		alda::bindings::record<
			Type
		>
	>,
	Type const &_value
)
{
	return
		sizeof(
			typename
			alda::bindings::record<
				Type
			>::length_type
		)
		+
		_value.size();
}

template<
	typename Type
>
void
place(
	majutsu::dispatch_type<
		alda::bindings::record<
			Type
		>
	> const _concept,
	Type const &_value,
	majutsu::raw::pointer _mem
)
{
	alda::bindings::detail::put_length(
		_concept,
		_value,
		_mem
	);

	std::copy_n(
		_value.data(),
		_value.size(),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::dispatch_type<
		alda::bindings::record<
			Type
		>
	> const _concept,
	majutsu::raw::const_pointer const _mem
)
{
	typedef
	typename
	alda::bindings::record<
		Type
	>::length_type
	length_type;

	length_type const length(
		alda::bindings::detail::extract_length(
			_concept,
			_mem
		)
	);

	typedef
	boost::iostreams::stream_buffer<
		boost::iostreams::array_source
	>
	streambuf;

	streambuf buffer(
		fcppt::cast::to_char_ptr<
			char const *
		>(
			_mem
			+
			sizeof(length_type)
		),
		length
		-
		sizeof(length_type)
	);

	std::istream stream(
		&buffer
	);

	return
		alda::serialization::detail::read::make_object<
			Type
		>(
			stream
		);
}

}
}

#endif
