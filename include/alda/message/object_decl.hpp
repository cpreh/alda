//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_MESSAGE_OBJECT_DECL_HPP_INCLUDED
#define ALDA_MESSAGE_OBJECT_DECL_HPP_INCLUDED

#include <alda/message/object_fwd.hpp> // IWYU pragma: keep
#include <alda/raw/element_type.hpp>

namespace alda::message
{

template <typename Id, typename Type>
class object
{
public:
  using binding = Type;

  using element_type = alda::raw::element_type<Type>;

  using id_type = Id;

  explicit object(element_type const &);

  explicit object(element_type &&);

  [[nodiscard]] element_type const &get() const;

private:
  element_type value_;
};

}

#endif
