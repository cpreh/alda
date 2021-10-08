//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_OBJECT_TO_BUFFER_HPP_INCLUDED
#define ALDA_MESSAGE_OBJECT_TO_BUFFER_HPP_INCLUDED

#include <alda/message/object_impl.hpp>
#include <alda/raw/buffer.hpp>
#include <alda/raw/to_buffer.hpp>

namespace alda::message
{

template <typename Id, typename Type>
inline alda::raw::buffer object_to_buffer(alda::message::object<Id, Type> const &_value)
{
  return alda::raw::to_buffer<Type>(_value.get());
}

}

#endif
