#...............................................................................
#
#  This file is part of the AXL library.
#
#  AXL is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/axl/license.txt
#
#...............................................................................

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
	export CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
	export CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
	export CMAKE_DIR=$TRAVIS_BUILD_DIR/cmake-$CMAKE_VERSION
	export PATH=$CMAKE_DIR/bin:$PATH

	# lcov doesn't work with clang on ubuntu out-of-the-box
	# also, coverage should be collected without optimizations

	if [ "$CC" != "clang" ] && [ "$BUILD_CONFIGURATION" == "Debug" ]; then
		export GET_COVERAGE=ON
	fi

	if [ "$TARGET_CPU" == "amd64" ] && \
	   [ "$CC" == "gcc" ] && \
	   [ "$BUILD_CONFIGURATION" == "Release" ]; then
		export BUILD_DOC=ON
 	fi
fi
