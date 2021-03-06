// -*- C++ -*-
#ifndef ALIEN_HPDDMIMPL_HPDDMVECTOR_H
#define ALIEN_HPDDMIMPL_HPDDMVECTOR_H
/* Author : mesriy at Tue Jul 24 14:28:21 2012
 * Generated by createNew
 */

#include <alien/kernels/hpddm/HPDDMPrecomp.h>
#include <alien/core/impl/IVectorImpl.h>
#include <alien/data/ISpace.h>
#include <alien/distribution/VectorDistribution.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

BEGIN_HPDDMINTERNAL_NAMESPACE

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
template <typename ValueT> class VectorInternal;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

END_HPDDMINTERNAL_NAMESPACE

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Alien {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
template <typename ValueT, bool is_mpi> class HPDDMVector : public IVectorImpl
{
 public:
  typedef HPDDMInternal::VectorInternal<ValueT> VectorInternal;

 public:
  HPDDMVector(const MultiVectorImpl* multi_impl);

  virtual ~HPDDMVector();

 public:
  void init(const VectorDistribution& dist, const bool need_allocate);
  void allocate();

  void free() {}
  void clear() {}

 public:
  void setValues(const int nrows, ValueT const* values);

  void getValues(const int nrows, ValueT* values) const;

 public:
  VectorInternal* internal() { return m_internal.get(); }

  const VectorInternal* internal() const { return m_internal.get(); }

 private:
 private:
  std::unique_ptr<VectorInternal> m_internal;
  int m_local_offset;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif /* ALIEN_HPDDMIMPL_HPDDMVECTOR_H */
