#!/bin/sh
#----------------------------------------------------------------------------
# 02-Sep-2015 ShaneG
#
# This script creates the distribution archive that is used to set up new
# SensNode based projects
#----------------------------------------------------------------------------
BASEDIR=`dirname $0`
BASEDIR=`readlink -f ${BASEDIR}`

# Set up source directories
DIR_DIST=${BASEDIR}/dist
DIR_LIBS=${BASEDIR}/lib
DIR_INCL=${BASEDIR}/include

# Supported targets
TARGETS="lpc1114 xmc1100"

# Clean the existing directory if needed
if [ -d ${DIR_DIST} ]; then
  rm -rf ${DIR_DIST}
fi

# Build everything
cd ${BASEDIR}
make superclean
for target in ${TARGETS}; do
  make clean
  make TARGET=${target} || exit 1
done

# Copy libraries and headers
mkdir -p ${DIR_DIST}/sensnode
cp -R ${DIR_LIBS} ${DIR_DIST}/sensnode
cp -R ${DIR_INCL} ${DIR_DIST}/sensnode

# Add the target Makefile definitions
for target in ${TARGETS}; do
  cp ${target}/Makefile.inc ${DIR_DIST}/sensnode/include/boards/${target}.mk
done

# TODO: Copy version, changelog and makefile
cp ${BASEDIR}/VERSION ${DIR_DIST}/sensnode
cp ${BASEDIR}/CHANGELOG ${DIR_DIST}/sensnode
cp ${BASEDIR}/Makefile.template ${DIR_DIST}/Makefile
cp ${BASEDIR}/README.template ${DIR_DIST}/README
cp ${BASEDIR}/LICENSE.template ${DIR_DIST}/sensnode/LICENSE

# Clean up editor backups
rm -f `find ${DIR_DIST} -name '*~' -type f`

# Create the archive
cd ${DIR_DIST}
ARCHIVE=sensnode-`awk '{ print $ 1}' <sensnode/VERSION`.tgz
tar -czf ${ARCHIVE} sensnode Makefile README
echo "Created archive ${DIR_DIST}/${ARCHIVE}"

