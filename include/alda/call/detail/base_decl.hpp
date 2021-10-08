//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_CALL_DETAIL_BASE_DECL_HPP_INCLUDED
#define ALDA_CALL_DETAIL_BASE_DECL_HPP_INCLUDED

#include <alda/call/detail/base_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace alda::call::detail
{

template <typename TypeEnum, typename Callee>
class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base() = 0;

  using message_type = alda::message::base<TypeEnum>;

  virtual typename Callee::result_type call(Callee &, message_type const &) const = 0;
};

}

#endif
