#!/bin/bash
DYLD_IMAGE_SUFFIX=_debug
export DYLD_IMAGE_SUFFIX
exec /Users/liliangarcia/Qt/6.5.0/macos/libexec/rcc "$@"
