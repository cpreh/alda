//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_DETAIL_READ_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_IMPL_HPP_INCLUDED

#include <alda/serialization/istream_fwd.hpp>
#include <alda/serialization/detail/read_decl.hpp>

template <typename TypeEnum>
alda::serialization::detail::read<TypeEnum>::read(alda::serialization::istream &_stream)
    : stream_(_stream)
{
}

#endif
