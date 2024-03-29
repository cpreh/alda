//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_SERIALIZATION_IMPL_CONTEXT_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_IMPL_CONTEXT_IMPL_HPP_INCLUDED

#include <alda/serialization/context_decl.hpp> // IWYU pragma: export
#include <alda/serialization/detail/dispatch/base_decl.hpp> // IWYU pragma: keep

template <typename TypeEnum>
alda::serialization::context<TypeEnum>::context() : handlers_()
{
}

namespace alda::serialization
{
template <typename TypeEnum>
context<TypeEnum>::~context() = default;
}

template <typename TypeEnum>
typename alda::serialization::context<TypeEnum>::dispatch_map const &
alda::serialization::context<TypeEnum>::handlers() const
{
  return handlers_;
}

#endif
