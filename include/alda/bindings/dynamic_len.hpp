#ifndef ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED
#define ALDA_BINDINGS_DYNAMIC_LEN_HPP_INCLUDED

#include <alda/bindings/dynamic_len_fwd.hpp>
#include <alda/bindings/detail/extract_length.hpp>
#include <alda/bindings/detail/put_length.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/make.hpp>
#include <majutsu/needed_size.hpp>
#include <majutsu/place.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct dynamic_len
{
	typedef Type type;

	typedef std::uint16_t length_type;
};

template<
	typename Type,
	typename Adapted
>
majutsu::size_type
needed_size(
	alda::bindings::dynamic_len<
		Type,
		Adapted
	> const *,
	Type const &_value
)
{
	majutsu::size_type ret(
		sizeof(
			typename alda::bindings::dynamic_len<
				Type,
				Adapted
			>::length_type
		)
	);

	for(
		auto const &elem : _value
	)
		ret +=
			majutsu::needed_size<
				Adapted
			>(
				elem
			);

	return ret;
}

template<
	typename Type,
	typename Adapted
>
void
place(
	alda::bindings::dynamic_len<
		Type,
		Adapted
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

	for(
		auto const &elem : _value
	)
	{
		majutsu::place<
			Adapted
		>(
			elem,
			_mem
		);

		_mem +=
			majutsu::needed_size<
				Adapted
			>(
				elem
			);
	}
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	alda::bindings::dynamic_len<
		Type,
		Adapted
	> const *const _concept,
	majutsu::const_raw_pointer const _mem
)
{
	typedef typename alda::bindings::dynamic_len<
		Type,
		Adapted
	>::length_type length_type;

	length_type const my_size(
		alda::bindings::detail::extract_length(
			_concept,
			_mem
		)
	);

	Type ret;

	for(
		majutsu::const_raw_pointer cur_mem(
			_mem + sizeof(length_type)
		);
		cur_mem != _mem + my_size;
	)
	{
		typename Type::value_type elem(
			majutsu::make<
				Adapted
			>(
				cur_mem
			)
		);

		ret.push_back(
			elem
		);

		cur_mem +=
			majutsu::needed_size<
				Adapted
			>(
				elem
			);
	}

	return ret;
}

}
}

#endif
