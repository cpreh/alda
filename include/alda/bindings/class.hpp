#ifndef ALDA_BINDINGS_CLASS_HPP_INCLUDED
#define ALDA_BINDINGS_CLASS_HPP_INCLUDED

#include <alda/bindings/class_decl.hpp>
#include <alda/bindings/dynamic_len.hpp>
#include <alda/bindings/detail/extract_length.hpp>
#include <alda/bindings/detail/put_length.hpp>
#include <alda/serialization/detail/read/make_object.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type
>
majutsu::size_type
needed_size(
	alda::bindings::class_<
		Type
	> const *,
	Type const &_value
)
{
	return
		sizeof(
			typename
			alda::bindings::class_<
				Type
			>::length_type
		)
		+
		_value.memory().size();
}

template<
	typename Type
>
void
place(
	alda::bindings::class_<
		Type
	> const *const _concept,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	alda::bindings::detail::put_length(
		_concept,
		_value,
		_mem
	);

	fcppt::algorithm::copy_n(
		_value.memory().data(),
		_value.memory().size(),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	alda::bindings::class_<
		Type
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef
	typename
	alda::bindings::class_<
		Type
	>::length_type
	length_type;

	length_type const length(
		alda::bindings::detail::extract_length(
			_concept,
			_mem
		)
	);

	typedef boost::iostreams::stream_buffer<
		boost::iostreams::array_source
	> streambuf;

	streambuf buffer(
		fcppt::cast::to_char_ptr<
			char const *
		>(
			_mem + sizeof(length_type)
		),
		length  - sizeof(length_type)
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
