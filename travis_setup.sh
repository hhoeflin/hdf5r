#!/bin/bash

if [ "$TRAVIS_OS_NAME" == "osx" ]; then # use homebrew version
  brew update
  brew install hdf5
  echo "brew install finished"
else # install from source
  cd ..
  if [ "${HDF5_VERSION:0:4}" == "1.10" ]; then
    wget "$HDF5_RELEASE_URL/hdf5-1.10/hdf5-1.10.1/src/hdf5-1.10.1.tar.gz"
  else
    wget "$HDF5_RELEASE_URL/hdf5-1.8/hdf5-$HDF5_VERSION/src/hdf5-$HDF5_VERSION.tar.gz"
  fi
  tar -xzf "hdf5-$HDF5_VERSION.tar.gz"
  cd "hdf5-$HDF5_VERSION"
  ./configure --prefix=/usr/local
  sudo make install
  cd ../hdf5r
fi
