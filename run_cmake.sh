#! /bin/sh
mkdir BUILD.bluelink && cd "$_"
# CAPI_ROOT to cotain pslse/
cmake -DCAPI_ROOT=/home/vinay/work/capi -DCAPI_SIM=ON -DCAPI_BUILD_TYPE=SIM ../BlueLink/

