#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/che4ve/MAI/LabsOOP/2/Build
  make -f /Users/che4ve/MAI/LabsOOP/2/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/che4ve/MAI/LabsOOP/2/Build
  make -f /Users/che4ve/MAI/LabsOOP/2/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/che4ve/MAI/LabsOOP/2/Build
  make -f /Users/che4ve/MAI/LabsOOP/2/Build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/che4ve/MAI/LabsOOP/2/Build
  make -f /Users/che4ve/MAI/LabsOOP/2/Build/CMakeScripts/ReRunCMake.make
fi
