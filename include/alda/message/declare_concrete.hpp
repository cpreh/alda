//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_DECLARE_CONCRETE_HPP_INCLUDED
#define ALDA_MESSAGE_DECLARE_CONCRETE_HPP_INCLUDED

#include <alda/detail/export_external_class_instantiation.hpp>
#include <alda/message/concrete_decl.hpp>

#define ALDA_MESSAGE_DECLARE_CONCRETE(type_enum, message_type) \
  extern template class ALDA_DETAIL_EXPORT_EXTERNAL_CLASS_INSTANTIATION \
      alda::message::concrete<type_enum, message_type>

#endif
