#!/bin/bash
#
# Wrapper for compiling code examples using cmake.

###########################################################################################
# Global parameters
###########################################################################################
readonly script_dir=$(dirname ${0})
readonly project_root=$(cd ${script_dir} && pwd)
readonly mode="$1"
readonly args="${@:2}"

###########################################################################################
# Load modules for compiling on Bridges
###########################################################################################

bridges_load_modules () {
  if command -v module >/dev/null; then
    module load cmake/3.11.4
    module load gcc/7.3.0
  fi
}

###########################################################################################
# Load modules for compiling on Virtual Machine
###########################################################################################

virtual_machine_load_modules () {
  if command -v module >/dev/null; then
    if module is-avail gcc/7.3.0; then
      module load gcc/7.3.0
    fi
  fi
}

###########################################################################################
# Compile source code for examples
#
# Globals:
#   project_root                           # Absolute path of project root
# Arguments:
#   1: CMake build directory               # default: build"
# Returns:
#   None
###########################################################################################

compile () {
  local cmake_build_dir="${1:-build}"

  if [[ ! -d ${project_root}/${cmake_build_dir} ]]; then
    mkdir -p ${project_root}/${cmake_build_dir}
    cd ${project_root}/${cmake_build_dir}
    CC=gcc CXX=g++ cmake -DCMAKE_BUILD_TYPE=Release ../
    cmake ../
    make -j4
    make install
  else
    cd ${project_root}/${cmake_build_dir}
    make -j4
    make install
  fi

  cd ${project_root}
}

###########################################################################################
# Main script
###########################################################################################

if [[ ${mode} == "bridges" ]]; then
  bridges_load_modules
  compile ${args}
elif [[ ${mode} == "vm" ]]; then
  virtual_machine_load_modules
  compile ${args}
elif [[ ${mode} == "help" || ${mode} == "--help" || ${mode} == "-h" ]]; then
  echo "make.sh - Wrapper for compiling code examples"
  echo ""
  echo "Usage: make.sh [mode] [position_arguments ..]"
  echo ""
  echo "Mode:"
  echo "  bridges (default)                           # Compile on Bridges"
  echo "  vm                                          # Compile on Virtual Machine"
  echo ""
  echo "Position Arguments:"
  echo "  1: CMake build directory                     # default: build"
else
  bridges_load_modules
  compile ${args}
fi

