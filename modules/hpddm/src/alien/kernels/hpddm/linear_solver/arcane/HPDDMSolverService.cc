// -*- C++ -*-
/* Author : couletj at Thu Jul 25 09:24:07 2019
 * Generated by createNew
 */

/* INFO: Les services et modules se conforment maintenant � la politique Arcane core.
 *       L'emploi des .h �tait fictif.
 *       D�sormais les d�clarations de classe pour les modules et services seront
 *       localis�es dans le fichier .cc correspondant.
 */

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <alien/utils/Precomp.h>
#include <alien/AlienHPDDMPrecomp.h>

#include <alien/kernels/hpddm/HPDDMPrecomp.h>
#include <alien/kernels/hpddm/HPDDMBackEnd.h>
#include <alien/core/backend/LinearSolver.h>
#include <alien/kernels/hpddm/linear_solver/HPDDMOptionTypes.h>
#include <ALIEN/axl/HPDDMSolver_axl.h>

#include <alien/kernels/hpddm/linear_solver/HPDDMInternalSolver.h>
#include <ALIEN/axl/HPDDMSolver_StrongOptions.h>

namespace Alien {

class ALIEN_HPDDM_EXPORT HPDDMLinearSolver : public ArcaneHPDDMSolverObject,
                                             public HPDDMInternalSolver
//, public LinearSolver<BackEnd::tag::htssolver>
{
 public:
/** Constructeur de la classe */

#ifdef ALIEN_USE_ARCANE
  HPDDMLinearSolver(const Arcane::ServiceBuildInfo& sbi);
#endif

  HPDDMLinearSolver(
      IMessagePassingMng* parallel_mng, std::shared_ptr<IOptionsHPDDMSolver> _options);

  /** Destructeur de la classe */
  virtual ~HPDDMLinearSolver(){};
};

/** Constructeur de la classe */

#ifdef ALIEN_USE_ARCANE
HPDDMLinearSolver::HPDDMLinearSolver(const Arcane::ServiceBuildInfo& sbi)
: ArcaneHPDDMSolverObject(sbi)
, Alien::HPDDMInternalSolver(
      sbi.subDomain()->parallelMng()->messagePassingMng(), options())
//, LinearSolver<BackEnd::tag::htssolver>(sbi.subDomain()->parallelMng(), options())
{
}
#endif

HPDDMLinearSolver::HPDDMLinearSolver(
    IMessagePassingMng* parallel_mng, std::shared_ptr<IOptionsHPDDMSolver> _options)
: ArcaneHPDDMSolverObject(_options)
, Alien::HPDDMInternalSolver(parallel_mng, options())
//, LinearSolver<BackEnd::tag::hpddm>(parallel_mng, options())
{
}

/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_HPDDMSOLVER(HPDDMSolver, HPDDMLinearSolver);
}

REGISTER_STRONG_OPTIONS_HPDDMSOLVER();
