//          Copyright Carl Philipp Reh 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED
#define ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED

#include <alda/call/detail/base_impl.hpp>
#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/any_of.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/mpl/list/index_of_if.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace alda::call::detail
{

template <typename TypeEnum, typename Messages, typename Callee>
struct make_instance
{
  using base = alda::call::detail::base<TypeEnum, Callee>;

  using optional_base_unique_ptr = fcppt::optional::object<fcppt::unique_ptr<base>>;

  template <typename Type>
  using has_message = fcppt::mpl::list::any_of<
      Messages,
      fcppt::mpl::bind<
          fcppt::mpl::lambda<std::is_same>,
          fcppt::mpl::constant<Type>,
          fcppt::mpl::lambda<alda::message::detail::extract_id>>>;

  template <typename Type>
  typename std::enable_if<has_message<Type>::value, optional_base_unique_ptr>::type
  operator()(Type) const
  {
    return optional_base_unique_ptr{fcppt::unique_ptr_to_base<base>(
        fcppt::make_unique_ptr<alda::call::detail::concrete<
            TypeEnum,
            Callee,
            fcppt::mpl::list::at<
                Messages,
                fcppt::mpl::list::index_of_if<
                    Messages,
                    fcppt::mpl::bind<
                        fcppt::mpl::lambda<std::is_same>,
                        fcppt::mpl::constant<Type>,
                        fcppt::mpl::lambda<alda::message::detail::extract_id>>>>>>())};
  }

  template <typename Type>
  typename std::enable_if<!has_message<Type>::value, optional_base_unique_ptr>::type
  operator()(Type) const
  {
    return optional_base_unique_ptr();
  }
};

}

#endif
