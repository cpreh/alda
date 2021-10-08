//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_DECL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_BASE_DECL_HPP_INCLUDED

#include <alda/detail/external_class_symbol.hpp>
#include <alda/detail/external_symbol.hpp>
#include <alda/message/base_unique_ptr.hpp>
#include <alda/serialization/detail/read_fwd.hpp>
#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace alda::serialization::detail::dispatch
{

template <typename TypeEnum>
class ALDA_DETAIL_EXTERNAL_CLASS_SYMBOL base
{
  FCPPT_NONMOVABLE(base);

protected:
  ALDA_DETAIL_EXTERNAL_SYMBOL
  base();

public:
  using message_unique_ptr = alda::message::base_unique_ptr<TypeEnum>;

  using reader = alda::serialization::detail::read<TypeEnum>;

  ALDA_DETAIL_EXTERNAL_SYMBOL
  virtual ~base() = 0;

  [[nodiscard]] virtual message_unique_ptr on_dispatch(reader const &) const = 0;
};

}

#endif
