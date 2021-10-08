//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_INSTANTIATE_BASE_HPP_INCLUDED
#define ALDA_MESSAGE_INSTANTIATE_BASE_HPP_INCLUDED

#include <alda/message/impl/base_impl.hpp>

#define ALDA_MESSAGE_INSTANTIATE_BASE(type_enum) template class alda::message::base<type_enum>

#endif
