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

#ifndef __ETL_MULTI_ARRAY__
#define __ETL_MULTI_ARRAY__

#include <stdint.h>

#include "array.h"

///\defgroup multi_array multi_array
/// A template for easier definition of multi-dimensional arrays.
///\ingroup  containers

namespace etl
{  
  //***************************************************************************
  /// Multi-array for 4 dimensions.
  ///\ingroup multi_array
  //***************************************************************************
  template <typename T, const size_t S0, const size_t S1 = 0, const size_t S2 = 0, const size_t S3 = 0>
  class multi_array
  {
  public:

    typedef T value_type;
    typedef typename etl::array<etl::array<etl::array<etl::array<T, S3>, S2>, S1>, S0> type0;
    typedef typename etl::array<etl::array<etl::array<T, S3>, S2>, S1> type1;
    typedef typename etl::array<etl::array<T, S3>, S2> type2;
    typedef typename etl::array<T, S3> type3;

    enum
    {
      DIMENSIONS = 4,
      SIZE0 = S0,
      SIZE1 = S1,
      SIZE2 = S2,
      SIZE3 = S3
    };

    type1& operator[](size_t i)
    {
      return data[i];
    }

    const type1& operator[](size_t i) const
    {
      return data[i];
    }

    static size_t size(size_t i = 0)
    {
      switch (i)
      {
        case 0:  return SIZE0;
        case 1:  return SIZE1;
        case 2:  return SIZE2;
        case 3:  return SIZE3;
        default: return 0;
      }
    }

    /// The number of dimensions.
    static size_t dimensions(size_t i = 0)
    {
      switch (i)
      {
        case 0:  return DIMENSIONS;
        case 1:  return DIMENSIONS - 1;
        case 2:  return DIMENSIONS - 2;
        case 3:  return DIMENSIONS - 3;
        default: return 0;
      }
    }

  //private:

    type1 data;
  };

  //***************************************************************************
  /// Multi-array for 3 dimensions.
  ///\ingroup multi_array
  //***************************************************************************
  template <typename T, const size_t S0, const size_t S1, const size_t S2>
  class multi_array<T, S0, S1, S2, 0>
  {      
  public:

    typedef T value_type;
    typedef typename etl::multi_array<T, S1, S2> type;
    typedef typename type::type type1;

    enum
    {
      DIMENSIONS = 3,
      SIZE0 = S0,
      SIZE1 = S1,
      SIZE2 = S2/*,
      SIZE3 = 0*/
    };

    type& operator[](size_t i)
    {
      return data[i];
    }

    const type& operator[](size_t i) const
    {
      return data[i];
    }

    static size_t size()
    {
      return SIZE0;
    }
    
    /// The number of dimensions.
    static size_t dimensions()
    {
      return DIMENSIONS;
    }
      
  private:
    
    etl::array<type, SIZE0> data; 
  };

  //***************************************************************************
  /// Multi-array for 2 dimensions.
  ///\ingroup multi_array
  //***************************************************************************
  template <typename T, const size_t S0, const size_t S1>
  class multi_array<T, S0, S1, 0, 0>
  {       
  public:

    typedef T value_type;
    typedef typename etl::multi_array<T, S1> type;

    enum
    {
      DIMENSIONS = 2,
      SIZE0 = S0,
      SIZE1 = S1,
      SIZE2 = 0,
      SIZE3 = 0
    };

    type& operator[](size_t i)
    {
      return data[i];
    }

    const type& operator[](size_t i) const
    {
      return data[i];
    }

    static size_t size()
    {
      return SIZE0;
    }
    
    /// The number of dimensions.
    static size_t dimensions()
    {
      return DIMENSIONS;
    }

  private:
    
    etl::array<type, SIZE0> data; 
  };

  //***************************************************************************
  /// Multi-array for 1 dimension.
  //***************************************************************************
  template <typename T, const size_t S0>
  class multi_array<T, S0, 0, 0, 0>
  {
  public:

    typedef T value_type;
    typedef typename etl::array<T, S0> type;
    
    enum
    {
      DIMENSIONS = 1,
      SIZE0 = S0,
      SIZE1 = 0,
      SIZE2 = 0,
      SIZE3 = 0
    };

    type& operator[](size_t i)
    {
      return data[i];
    }
    
    const type& operator[](size_t i) const
    {
      return data[i];
    }

    static size_t size()
    {
      return SIZE0;
    }

    /// The number of dimensions.
    static size_t dimensions()
    {
      return DIMENSIONS;
    }

  private:
    
    type data;         
  };

  template <typename T>
  class multi_array_view
  {
  public:

    template <typename TArray>
    multi_array_view(TArray &a)
      : dim(a.DIMENSIONS)
    {
      sizes[0] = a.SIZE0;
      sizes[1] = a.SIZE1;
      sizes[2] = a.SIZE2;
      //sizes[3] = a.SIZE3;
    }

    size_t dimensions() const
    {
      return dim;
    }

    size_t size(size_t i) const
    {
      if (i < 4)
      {
        return sizes[i];
      }
      else
      {
        return 0;
      }
    }

    T& operator ()(size_t i0, size_t i1 = 0, size_t i2 = 0, size_t i3 = 0)
    {
      switch (dim)
      {
        case 1:
        {
          return pdata[i0];
          break;
        }

        case 2:
        {
          return 0; // pdata[(i0 * size0) + i1];
          break;
        }

        case 3:
        {
          return 0; //pdata[(i0 * size0) + i2];
          break;
        }

        case 4:
        {
          return 0; //pdata[(i0 * size0) + i3];
          break;
        }

        default:
        {
          assert(true);
          return 0;
          break;
        }
      }
    }

  private:

    T * pdata;
    uint_least8_t dim;
    size_t sizes[4];
  };
}

#endif
