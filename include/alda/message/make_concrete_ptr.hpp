//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED
#define ALDA_MESSAGE_MAKE_CONCRETE_PTR_HPP_INCLUDED

#include <alda/message/base_decl.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/message/concrete_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

namespace alda::message
{

template <typename TypeEnum, typename Message>
alda::message::base_unique_ptr<TypeEnum> make_concrete_ptr(Message const &_value)
{
  return fcppt::unique_ptr_to_base<alda::message::base<TypeEnum>>(
      fcppt::make_unique_ptr<alda::message::concrete<TypeEnum, Message>>(_value));
}

}

#endif
