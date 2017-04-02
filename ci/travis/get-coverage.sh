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

if [ "$TRAVIS_OS_NAME" == "linux" ] && [ "$CC" == "clang" ]; then
	return # lcov doesn't work with clang on ubuntu out-of-the-box
fi

if [ "$BUILD_CONFIGURATION" != "Debug" ]; then
	return # coverage should be collected without optimizations
fi

lcov --capture --directory . --no-external --output-file coverage.info
lcov --list coverage.info

curl -s https://codecov.io/bash | bash
