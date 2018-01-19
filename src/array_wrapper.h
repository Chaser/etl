///\file

/******************************************************************************
The MIT License(MIT)

Embedded Template Library.
https://github.com/ETLCPP/etl
https://www.etlcpp.com

Copyright(c) 2017 jwellbelove

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/

#ifndef __ETL_ARRAY_WRAPPER__
#define __ETL_ARRAY_WRAPPER__

#include "platform.h"
#include "iterator.h"
#include "error_handler.h"
#include "exception.h"
#include "hash.h"
#include "container.h"

#include <algorithm>

///\defgroup array array
/// A wrapper for arrays
///\ingroup containers

#undef ETL_FILE
#define ETL_FILE "42"

namespace etl
{
  //***************************************************************************
  /// The base class for array_wrapper exceptions.
  //***************************************************************************
  class array_wrapper_exception : public exception
  {
  public:

    array_wrapper_exception(string_type reason_, string_type file_name_, numeric_type line_number_)
      : exception(reason_, file_name_, line_number_)
    {
    }
  };

  //***************************************************************************
  ///\ingroup stack
  /// The exception thrown when the index is out of bounds.
  //***************************************************************************
  class array_wrapper_bounds : public array_wrapper_exception
  {
  public:

    array_wrapper_bounds(string_type file_name_, numeric_type line_number_)
      : array_wrapper_exception(ETL_ERROR_TEXT("array_wrapper:bounds", ETL_FILE"A"), file_name_, line_number_)
    {
    }
  };

  ////***************************************************************************
  /////\ingroup stack
  ///// The exception thrown when the view is uninitialised.
  ////***************************************************************************
  //class array_wrapper_uninitialised : public array_wrapper_exception
  //{
  //public:

  //  array_wrapper_uninitialised(string_type file_name_, numeric_type line_number_)
  //    : array_wrapper_exception(ETL_ERROR_TEXT("array_wrapper:uninitialised", ETL_FILE"B"), file_name_, line_number_)
  //  {
  //  }
  //};

  class array_temp
  {

  };

  //***************************************************************************
  /// Array wrapper.
  //***************************************************************************
  template <typename T, std::size_t SIZE_, T(&ARRAY_)[SIZE_]>
  class array_wrapper
  {
  public:

    typedef T                                     value_type;
    typedef std::size_t                           size_type;
    typedef T&                                    reference;
    typedef const T&                              const_reference;
    typedef T*                                    pointer;
    typedef const T*                              const_pointer;
    typedef T*                                    iterator;
    typedef const T*                              const_iterator;
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    enum
    {
      SIZE   = SIZE_,
      FRONT  = 0,
      BACK   = SIZE - 1,
      BEGIN  = 0,
      END    = SIZE,
      RBEGIN = SIZE - 1,
      REND   = -1
    };

    //*************************************************************************
    /// Returns a reference to the first element.
    //*************************************************************************
    ETL_CONSTEXPR reference front()
    {
      return *&ARRAY_[FRONT];
    }

    //*************************************************************************
    /// Returns a const reference to the first element.
    //*************************************************************************
    ETL_CONSTEXPR const_reference front() const
    {
      return *&ARRAY_[FRONT];
    }

    //*************************************************************************
    /// Returns a reference to the last element.
    //*************************************************************************
    ETL_CONSTEXPR reference back()
    {
      return *&ARRAY_[BACK];
    }

    //*************************************************************************
    /// Returns a const reference to the last element.
    //*************************************************************************
    ETL_CONSTEXPR const_reference back() const
    {
      return *&ARRAY_[BACK];
    }

    //*************************************************************************
    /// Returns a pointer to the first element of the internal storage.
    //*************************************************************************
    ETL_CONSTEXPR pointer data()
    {
      return &ARRAY_[BEGIN];
    }

    //*************************************************************************
    /// Returns a const pointer to the first element of the internal storage.
    //*************************************************************************
    ETL_CONSTEXPR const_pointer data() const
    {
      return &ARRAY_[BEGIN];
    }

    //*************************************************************************
    /// Returns an iterator to the beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR iterator begin()
    {
      return &ARRAY_[BEGIN];
    }

    //*************************************************************************
    /// Returns a const iterator to the beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_iterator begin() const
    {
      return &ARRAY_[BEGIN];
    }

    //*************************************************************************
    /// Returns a const iterator to the beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_iterator cbegin() const
    {
      return &ARRAY_[BEGIN];
    }

    //*************************************************************************
    /// Returns an iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR iterator end()
    {
      return &ARRAY_[END];
    }

    //*************************************************************************
    /// Returns a const iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_iterator end() const
    {
      return &ARRAY_[END];
    }

    //*************************************************************************
    // Returns a const iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_iterator cend() const
    {
      return &ARRAY_[END];
    }

    //*************************************************************************
    // Returns an reverse iterator to the reverse beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR reverse_iterator rbegin()
    {
      return reverse_iterator(&ARRAY_[END]);
    }

    //*************************************************************************
    /// Returns a const reverse iterator to the reverse beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator(&ARRAY_[END]);
    }

    //*************************************************************************
    /// Returns a const reverse iterator to the reverse beginning of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_reverse_iterator crbegin() const
    {
      return const_reverse_iterator(&ARRAY_[END]);
    }

    //*************************************************************************
    /// Returns a reverse iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR reverse_iterator rend()
    {
      return reverse_iterator(&ARRAY_[BEGIN]);
    }

    //*************************************************************************
    /// Returns a const reverse iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_reverse_iterator rend() const
    {
      return const_reverse_iterator(&ARRAY_[BEGIN]);
    }

    //*************************************************************************
    /// Returns a const reverse iterator to the end of the array.
    //*************************************************************************
    ETL_CONSTEXPR const_reverse_iterator crend() const
    {
      return const_reverse_iterator(&ARRAY_[BEGIN]);
    }

    //*************************************************************************
    /// Returns <b>true</b> if the array size is zero.
    //*************************************************************************
    ETL_CONSTEXPR bool empty() const
    {
      return (cbegin() == cend());
    }

    //*************************************************************************
    /// Returns the size of the array.
    //*************************************************************************
    ETL_CONSTEXPR size_t size() const
    {
      return SIZE;
    }

    //*************************************************************************
    /// Returns the maximum possible size of the array.
    //*************************************************************************
    ETL_CONSTEXPR size_t max_size() const
    {
      return SIZE;
    }

    ////*************************************************************************
    ///// Assign from iterators
    ////*************************************************************************
    //template <typename TIterator,
    //          typename TDummy = typename etl::enable_if<etl::is_random_iterator<TIterator>::value, void>::type>
    //void assign(TIterator begin_, TIterator end_)
    //{
    //  mbegin = etl::addressof(*begin_);
    //  mend = etl::addressof(*begin_) + std::distance(begin_, end_);
    //}

    ////*************************************************************************
    ///// Assign from iterator and size.
    ////*************************************************************************
    //template <typename TIterator,
    //          typename TSize,
    //          typename TDummy = typename etl::enable_if<etl::is_random_iterator<TIterator>::value, void>::type>
    //void assign(TIterator begin_, TSize size_)
    //{
    //  mbegin = etl::addressof(*begin_);
    //  mend = etl::addressof(*begin_) + size_;
    //}

    //*************************************************************************
    /// Returns a reference to the indexed value.
    //*************************************************************************
    ETL_CONSTEXPR reference operator[](size_t i)
    {
      return ARRAY_[i];
    }

    //*************************************************************************
    /// Returns a const reference to the indexed value.
    //*************************************************************************
    ETL_CONSTEXPR const_reference operator[](size_t i) const
    {
      return ARRAY_[i];
    }

    //*************************************************************************
    /// Returns a reference to the indexed value.
    //*************************************************************************
    ETL_CONSTEXPR reference at(size_t i)
    {
      ETL_ASSERT(i < SIZE, ETL_ERROR(array_wrapper_bounds));
      return ARRAY_[i];
    }

    //*************************************************************************
    /// Returns a const reference to the indexed value.
    //*************************************************************************
    ETL_CONSTEXPR const_reference at(size_t i) const
    {
      ETL_ASSERT(i < SIZE, ETL_ERROR(array_wrapper_bounds));
      return ARRAY_[i];
    }

    ////*************************************************************************
    ///// Equality for array views.
    ////*************************************************************************
    //friend bool operator == (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return (lhs.size() == rhs.size()) &&
    //         std::equal(lhs.begin(), lhs.end(), rhs.begin());
    //}

    ////*************************************************************************
    ///// Inequality for array views.
    ////*************************************************************************
    //friend bool operator != (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return !(lhs == rhs);
    //}

    ////*************************************************************************
    ///// Less-than for array views.
    ////*************************************************************************
    //friend bool operator < (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    //}

    ////*************************************************************************
    ///// Greater-than for array views.
    ////*************************************************************************
    //friend bool operator > (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return rhs < lhs;
    //}

    ////*************************************************************************
    ///// Less-than-equal for array views.
    ////*************************************************************************
    //friend bool operator <= (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return !(lhs > rhs);
    //}

    ////*************************************************************************
    ///// Greater-than-equal for array views.
    ////*************************************************************************
    //friend bool operator >= (const array_wrapper<T>& lhs, const array_wrapper<T>& rhs)
    //{
    //  return !(lhs < rhs);
    //}
  };

  template <typename T, std::size_t SIZE_, T(&ARRAY_)[SIZE_]>
  class const_array_wrapper
  {
  };

  //*************************************************************************
  /// Hash function.
  //*************************************************************************
#if ETL_8BIT_SUPPORT
  //template <typename T>
  //struct hash<etl::array_wrapper<T> >
  //{
  //  size_t operator()(const etl::array_wrapper<T>& view) const
  //  {
  //    return etl::__private_hash__::generic_hash<size_t>(reinterpret_cast<const uint8_t*>(&view[0]),
  //                                                       reinterpret_cast<const uint8_t*>(&view[view.size()]));
  //  }
  //};
 
  //template <typename T>
  //struct hash<etl::const_array_wrapper<T> >
  //{
  //  size_t operator()(const etl::const_array_wrapper<T>& view) const
  //  {
  //    return etl::__private_hash__::generic_hash<size_t>(reinterpret_cast<const uint8_t*>(&view[0]),
  //                                                       reinterpret_cast<const uint8_t*>(&view[view.size()]));
  //  }
  //};
#endif
}



#undef ETL_FILE

#endif

