// -*- C++ -*-
#ifndef ALIEN_IFPSOLVERIMPL_IFPSOLVERBACKEND_H
#define ALIEN_IFPSOLVERIMPL_IFPSOLVERBACKEND_H
/* Author : havep at Fri Jul 20 17:03:41 2012
 * Generated by createNew
 */

#include <alien/utils/Precomp.h>
#include <alien/core/backend/BackEnd.h>
#include <alien/kernels/ifp/linear_solver/IFPInternalLinearSolver.h>

/*---------------------------------------------------------------------------*/

namespace Alien {

/*---------------------------------------------------------------------------*/

class IFPInternalLinearSolver;
class IFPMatrix;
class IFPVector;
class Space;
class ILinearSolver;
template <class Matrix, class Vector> class IInternalLinearAlgebra;
// template <class Matrix, class Vector> class IInternalLinearSolver;

/*
extern IInternalLinearAlgebra<IFPMatrix, IFPVector>*
IFPInternalLinearAlgebraFactory(const Space& space);
*/

extern ILinearSolver* IFPInternalLinearSolverFactory(
    Arccore::MessagePassing::IMessagePassingMng* p_mng);

/*---------------------------------------------------------------------------*/

namespace BackEnd {
  namespace tag {
    struct ifpsolver
    {
    };
  }
}

template <> struct AlgebraTraits<BackEnd::tag::ifpsolver>
{
  // typedef void algebra_type; // pas d'algèbre associé
  typedef IFPMatrix matrix_type;
  typedef IFPVector vector_type;
  // typedef IInternalLinearAlgebra<matrix_type, vector_type> algebra_type;
  typedef ILinearSolver solver_type;

  /*
  static algebra_type* algebra_factory(const Space& space)
  {
    return nullptr;
  }
  */

  static solver_type* solver_factory(Arccore::MessagePassing::IMessagePassingMng* p_mng)
  {
    return IFPInternalLinearSolverFactory(p_mng);
  }
  static BackEndId name() { return "ifpsolver"; }
  // static vector_type * createVector(const MultiVectorImpl * impl) { return new
  // vector_type(impl); }
};

/*---------------------------------------------------------------------------*/

} // namespace Alien

/*---------------------------------------------------------------------------*/

#endif /* ALIEN_IFPSOLVERIMPL_IFPSOLVERBACKEND_H */
