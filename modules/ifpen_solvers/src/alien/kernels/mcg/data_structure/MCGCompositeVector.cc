#include "mpi.h"

#include <alien/core/impl/MultiVectorImpl.h>
#include <alien/data/CompositeVector.h>
#include <alien/kernels/simple_csr/SimpleCSRBackEnd.h>
#include <alien/kernels/composite/CompositeBackEnd.h>
#include <alien/kernels/composite/CompositeVector.h>

#include "alien/kernels/mcg/MCGBackEnd.h"
#include "alien/kernels/mcg/data_structure/MCGInternal.h"
#include "alien/kernels/mcg/data_structure/MCGCompositeVector.h"

namespace Alien {

MCGCompositeVector::MCGCompositeVector(const MultiVectorImpl* multi_impl)
: IVectorImpl(multi_impl, AlgebraTraits<BackEnd::tag::mcgsolver_composite>::name())
{
  // get composite backend
  const CompositeKernel::Vector& v = multi_impl->get<BackEnd::tag::composite>();
  std::vector<std::pair<int, int>> composite_info(v.size());

  for (int i = 0; i < v.size(); ++i) {
    const int n = v[i].space().size();

    int block_size = 1;
    if (v[i].impl()->block()) {
      block_size = v[i].impl()->block()->sizeX();
    }

    composite_info[i].first = n;
    composite_info[i].second = block_size;
  }

  m_internal = new VectorInternal(composite_info);
}

MCGCompositeVector::~MCGCompositeVector()
{
  delete m_internal;
}

void
MCGCompositeVector::init(const VectorDistribution& dist, const bool need_allocate)
{
  if (need_allocate)
    allocate();
}

void
MCGCompositeVector::allocate()
{}

void
MCGCompositeVector::setValues(const int part, const double* values)
{
  const int n =
      m_internal->m_bvector[part].size() * m_internal->m_bvector[part].blockSize();
  double* data = m_internal->m_bvector[part].data();

  for (int i = 0; i < n; ++i)
    data[i] = values[i];
}

void
MCGCompositeVector::getValues(const int part, double* values) const
{
#if 1
  throw FatalErrorException(A_FUNCINFO, "Not implemented");
#else
  const VectorDistribution& dist = this->distribution();
  int block_size = 1;

  if (this->block())
    block_size = this->block()->sizeX();
  else if (this->vblock())
    throw FatalErrorException(A_FUNCINFO, "Not implemented yet for vblock");

  const double* data = m_internal->m_bvector.data();
  for (int i = 0; i < dist.localSize() * block_size; i++)
    values[i] = data[i];
#endif
}

void
MCGCompositeVector::update(const MCGCompositeVector& v)
{
  MCGInternal::checkParallel(this->distribution().isParallel());
  ALIEN_ASSERT((this == &v), ("Unexpected error"));
}

} // namespace Alien
