// -*- C++ -*-
#ifndef ALIEN_NUMERICS_LINEARALGEBRA2_MTLIMPL_MTLMATRIX_H
#define ALIEN_NUMERICS_LINEARALGEBRA2_MTLIMPL_MTLMATRIX_H
/* Author : mesriy at Tue Jul 24 15:56:45 2012
 * Generated by createNew
 */

#include <vector>

#include <alien/kernels/mtl/MTLPrecomp.h>
#include <alien/core/impl/IMatrixImpl.h>
#include <alien/data/ISpace.h>

/*---------------------------------------------------------------------------*/

namespace Alien::MTL4Internal {

class MatrixInternal;
}

/*---------------------------------------------------------------------------*/

namespace Alien {

/*---------------------------------------------------------------------------*/

class MTLMatrix : public IMatrixImpl
{
 public:
  typedef MTL4Internal::MatrixInternal MatrixInternal;

 public:
  MTLMatrix(const MultiMatrixImpl* multi_impl);
  virtual ~MTLMatrix();

 public:
  void clear() {}

 public:
  bool initMatrix(
      std::vector<std::size_t> const& offsets, const int rank, const int nproc);

  bool addMatrixValues(const int nrow, const int* rows, const int* ncols, const int* cols,
      const double* values);

  bool setMatrixValues(const int max_row_size, const int nrow, const int* rows,
      const int* row_offset, const int* cols, const double* values);

  bool setMatrixBlockValues(const int offset, const int max_row_size,
      const int equations_num, const int unknowns_num, const int nrow,
      const int* row_offset, const int* cols, const double* values);

  bool setInitValues(const int nrow, const int* rows, const double* values);

 public:
  MatrixInternal* internal() { return m_internal; }
  const MatrixInternal* internal() const { return m_internal; }

  //   void update(const Alien::SimpleCSRMatrix<double> & v);
  //   void update(const MTLMatrix & v);

 private:
  Arccore::Integer ijk(Arccore::Integer i, Arccore::Integer j, Arccore::Integer k,
      Arccore::Integer block_size, Arccore::Integer unknowns_num) const
  {
    return k * block_size + i * unknowns_num + j;
  }

  MatrixInternal* m_internal;
};

/*---------------------------------------------------------------------------*/

} // namespace Alien

/*---------------------------------------------------------------------------*/

#endif /* ALIEN_NUMERICS_LINEARALGEBRA2_MTLIMPL_MTLMATRIX_H */
