os_version=`lsb_release -r -s`
os_version=${os_version%%[.]*}

source /soft/irsrvsoft1/expl/eb/r11/centos_${os_version}/envs/toolchain.sh
module load gimkl/2018b
source /soft/irsrvsoft1/expl/eb/r11/centos_${os_version}/envs/arcuser.sh
source /soft/irsrvsoft1/expl/eb/r11/centos_${os_version}/envs/arcsolver-advanced.sh

module unload HPDDM
