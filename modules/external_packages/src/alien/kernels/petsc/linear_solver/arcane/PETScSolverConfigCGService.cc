/* Author : havep at Mon Jun 30 18:00:20 2008
 * Generated by createNew
 */

#include <alien/kernels/petsc/linear_solver/arcane/PETScSolverConfigCGService.h>
#include <ALIEN/axl/PETScSolverConfigCG_StrongOptions.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Alien {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/** Constructeur de la classe */

#ifdef ALIEN_USE_ARCANE
PETScSolverConfigCGService::PETScSolverConfigCGService(
    const Arcane::ServiceBuildInfo& sbi)
: ArcanePETScSolverConfigCGObject(sbi)
, PETScConfig(sbi.subDomain()->parallelMng()->isParallel())
{
  ;
}
#endif

PETScSolverConfigCGService::PETScSolverConfigCGService(
    Arccore::MessagePassing::IMessagePassingMng* parallel_mng,
    std::shared_ptr<IOptionsPETScSolverConfigCG> options)
: ArcanePETScSolverConfigCGObject(options)
, PETScConfig(parallel_mng->commSize() > 1)
{
  ;
}

//! Initialisation
void
PETScSolverConfigCGService::configure(
    KSP& ksp, const ISpace& space, const MatrixDistribution& distribution)
{
  alien_debug([&] { cout() << "configure PETSc cg solver"; });
  PETScInitType::apply(this, ksp, options()->initType());

  checkError(
      "Set solver tolerances", KSPSetTolerances(ksp, options()->stopCriteriaValue(),
                                   1e-15, PETSC_DEFAULT, options()->numIterationsMax()));

  checkError("Solver set type", KSPSetType(ksp, KSPCG));
  if (options()->right()) {
#ifndef PETSC_KSPSETPCSIDE_NEW
    checkError(
        " Set solver preconditioner side ", KSPSetPreconditionerSide(ksp, PC_RIGHT));
#else /* PETSC_KSPSETPCSIDE_NEW */
    checkError(" Set solver preconditioner side ", KSPSetPCSide(ksp, PC_RIGHT));
#endif /* PETSC_KSPSETPCSIDE_NEW */
    checkError(" Set solver unpreconditioned norm type ",
        KSPSetNormType(ksp, KSP_NORM_UNPRECONDITIONED));
  }

  IPETScPC* preconditioner = options()->preconditioner();
  {
    PC pc;
    checkError("Get preconditioner", KSPGetPC(ksp, &pc));

    bool needSetUp = preconditioner->needPrematureKSPSetUp();
    if (needSetUp) {
      checkError("Solver setup", KSPSetUp(ksp));
      preconditioner->configure(pc, space, distribution);
    } else {
      preconditioner->configure(pc, space, distribution);
      checkError("Solver setup", KSPSetUp(ksp));
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_PETSCSOLVERCONFIGCG(CG, PETScSolverConfigCGService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace Alien

REGISTER_STRONG_OPTIONS_PETSCSOLVERCONFIGCG();

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
