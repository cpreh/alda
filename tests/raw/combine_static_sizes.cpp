#include <alda/bindings/fundamental.hpp>
#include <alda/raw/combine_static_sizes.hpp>
#include <alda/raw/is_static_size.hpp>
#include <alda/raw/static_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/plus.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


int
main()
{
	static_assert(
		alda::raw::combine_static_sizes<
			boost::mpl::plus<
				boost::mpl::_1,
				boost::mpl::_2
			>,
			alda::raw::static_size<
				alda::bindings::fundamental<
					std::uint16_t
				>
			>,
			alda::raw::static_size<
				alda::bindings::fundamental<
					std::uint32_t
				>
			>
		>::value
		==
		alda::raw::static_size<
			alda::bindings::fundamental<
				std::uint16_t
			>
		>::value
		+
		alda::raw::static_size<
			alda::bindings::fundamental<
				std::uint32_t
			>
		>::value,
		""
	);

	static_assert(
		!alda::raw::is_static_size<
			alda::raw::combine_static_sizes<
				boost::mpl::plus<
					boost::mpl::_1,
					boost::mpl::_2
				>,
				alda::raw::static_size<
					alda::bindings::fundamental<
						std::uint16_t
					>
				>,
				alda::raw::static_size<
					void
				>
			>
		>::value,
		""
	);
}
