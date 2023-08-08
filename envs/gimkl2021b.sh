os_version=`lsb_release -r -s`
os_version=${os_version%%[.]*}

source /soft/irsrvsoft1/expl/eb/r11/el_${os_version}-x86_64/envs/toolchain.sh
module load gimkl/2021b
source /soft/irsrvsoft1/expl/eb/r11/el_${os_version}-x86_64/envs/arcuser.sh
source /soft/irsrvsoft1/expl/eb/r11/el_${os_version}-x86_64/envs/arcsolver-advanced.sh

module unload HPDDM

export MPI_ROOT=${MPI_ROOT}/mpi/2021.4.0
export IFORT_ROOT=${INTELCOMPILERS_ROOT}/compiler/2021.4.0/linux/compiler

