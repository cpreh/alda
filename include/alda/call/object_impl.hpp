//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_CALL_OBJECT_IMPL_HPP_INCLUDED
#define ALDA_CALL_OBJECT_IMPL_HPP_INCLUDED

#include <alda/call/object_decl.hpp> // IWYU pragma: export
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/call/detail/make_instance.hpp>
#include <alda/message/base_decl.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>

template <typename TypeEnum, typename Messages, typename Callee>
alda::call::object<TypeEnum, Messages, Callee>::object()
    : instances_(fcppt::enum_::array_init<instance_array>(
          alda::call::detail::make_instance<TypeEnum, Messages, Callee>{}))
{
}

namespace alda::call
{
template <typename TypeEnum, typename Messages, typename Callee>
object<TypeEnum, Messages, Callee>::~object() = default;
}

template <typename TypeEnum, typename Messages, typename Callee>
typename alda::call::object<TypeEnum, Messages, Callee>::result_type
alda::call::object<TypeEnum, Messages, Callee>::operator()(
    message_base const &_message, Callee &_callee, default_callback const &_default_callback) const
{
  return fcppt::optional::maybe(
      instances_[_message.type()],
      [&_message, &_default_callback] { return _default_callback(_message); },
      [&_callee, &_message](base_unique_ptr const &_dispatcher)
      { return _dispatcher->call(_callee, _message); });
}

#endif
