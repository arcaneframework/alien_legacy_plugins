/* Author : desrozis at Mon Jan 14 10:00:00 2019
 * Generated by createNew
 */

#ifndef PETSCSOLVERCONFIGLUSERVICE_H
#define PETSCSOLVERCONFIGLUSERVICE_H

#include <alien/kernels/petsc/PETScPrecomp.h>
#include <alien/AlienExternalPackagesPrecomp.h>

#include <alien/kernels/petsc/linear_solver/IPETScKSP.h>
#include <alien/kernels/petsc/linear_solver/IPETScPC.h>
#include <alien/kernels/petsc/linear_solver/PETScConfig.h>
#include <alien/kernels/petsc/linear_solver/PETScInitType.h>

#include <ALIEN/axl/PETScSolverConfigLU_axl.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Alien {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

class ALIEN_EXTERNAL_PACKAGES_EXPORT PETScSolverConfigLUService
    : public ArcanePETScSolverConfigLUObject,
      public PETScConfig
{
 public:
/** Constructeur de la classe */
#ifdef ALIEN_USE_ARCANE
  PETScSolverConfigLUService(const Arcane::ServiceBuildInfo& sbi);
#endif

  PETScSolverConfigLUService(Arccore::MessagePassing::IMessagePassingMng* parallel_mng,
      std::shared_ptr<IOptionsPETScSolverConfigLU> options);

  /** Destructeur de la classe */
  virtual ~PETScSolverConfigLUService() {}

 public:
  //! Initialisation
  void configure(KSP& ksp, const ISpace& space, const MatrixDistribution& distribution);
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace Alien

#endif // PETSCSOLVERCONFIGLUSERVICE_H
