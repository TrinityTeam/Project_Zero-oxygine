#!/bin/bash

until [ -z $1 ]
do
    printf '%s' ""

	case "$1" in
	    '-c'|'--cmake-options')
    		CMAKE_OPTIONS="$2"
            shift
    	;;
    	'-m'|'--make-options')
    		MAKE_OPTIONS="$2"
            shift
    	;;
    	'-r'|'--oxygine-root')
    		OXYGINE_ROOT=$(readlink -f "$2")
            shift
    	;;
    	'-b'|'--build-dir')
    		BUILD_DIR=$(readlink -f "$2")
            shift
        ;;
    	'-d'|'--data-dir')
    		DATA_DIR=$(readlink -f "$2")
            shift
    	;;
    	*)
    	    printf '%s\n' "Unknown option: $1"
    	;;
	esac
	shift
done

BUILD_DIR=${BUILD_DIR:-"$(readlink -f build)"}
DATA_DIR=${DATA_DIR:-"$(readlink -f ../data)"}

CMAKE_OPTIONS="$CMAKE_OPTIONS -DOXYGINE_ROOT=${OXYGINE_ROOT:?Error: Oxygine has not been found; Please specify OXYGINE_ROOT(set environment variable or specify with -r|--oxygine-root argument) to the proper path to the Oxygine}"

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

cmake .. $CMAKE_OPTIONS && make $MAKE_OPTIONS || exit 1

cd "$DATA_DIR"
"$BUILD_DIR"/Project_Zero
