#!/bin/bash
red='\033[0;31m'
green='\033[0;32m'
reset='\033[0m'
cyan='\033[0;36m'

if [ -d build ]; then
    echo -e ${cyan}"build dir found"${reset} 
    echo -e ${cyan}"rm build"${reset} 
    rm -r build
fi
mkdir build
echo -e ${cyan}"build begin"${reset}
time ./build.sh || exit 1
echo -e ${green}"build done"${reset}

echo -e ${cyan}"testing runfilters"${reset}
cp build/test/runfilters runfilters
if time ./runfilters data soccer; then
    echo -e ${green}"runfilters soccer success"${reset}
    if diff data/soccer_blurred.txt data/ref_output/soccer_blurred.txt; then
        echo -e ${green}'soccer_blurred passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_blurred'$cases${reset}
        exit 0
    fi

    if diff data/soccer_derx.txt data/ref_output/soccer_derx.txt; then
        echo -e ${green}'soccer_derx passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_derx'$cases${reset}
        exit 0
    fi

    if diff data/soccer_dery.txt data/ref_output/soccer_dery.txt; then
        echo -e ${green}'soccer_dery passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_dery'$cases${reset}
        exit 0
    fi

    if diff data/soccer_dermag.txt data/ref_output/soccer_dermag.txt; then
        echo -e ${green}'soccer_dermag passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_dermag'$cases${reset}
        exit 0
    fi
else
    echo -e ${red}"running failed"${reset}
    rm runfilters
    exit 1
fi
echo ''
if time ./runfilters data eiffel; then
    echo -e ${green}"runfilters eiffel success"${reset}
    if diff data/eiffel_blurred.txt data/ref_output/eiffel_blurred.txt; then
        echo -e ${green}'eiffel_blurred passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_blurred'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_derx.txt data/ref_output/eiffel_derx.txt; then
        echo -e ${green}'eiffel_derx passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_derx'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_dery.txt data/ref_output/eiffel_dery.txt; then
        echo -e ${green}'eiffel_dery passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_dery'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_dermag.txt data/ref_output/eiffel_dermag.txt; then
        echo -e ${green}'eiffel_dermag passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_dermag'$cases${reset}
        exit 0
    fi
else
    echo -e ${red}"running failed"${reset}
    rm runfilters
    exit 1
fi

rm runfilters
rm data/soccer_*.txt
rm data/eiffel_*.txt
echo -e ${green}"runfilters test done\nall tests passed"${reset}
echo ''

echo -e ${cyan}"testing runfiltersTh"${reset}
cp build/test/runfiltersTh runfiltersTh
if time ./runfiltersTh data soccer; then
    echo -e ${green}"runfiltersTh soccer success"${reset}
    if diff data/soccer_blurred.txt data/ref_output/soccer_blurred.txt; then
        echo -e ${green}'soccer_blurred passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_blurred'$cases${reset}
        exit 0
    fi

    if diff data/soccer_derx.txt data/ref_output/soccer_derx.txt; then
        echo -e ${green}'soccer_derx passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_derx'$cases${reset}
        exit 0
    fi

    if diff data/soccer_dery.txt data/ref_output/soccer_dery.txt; then
        echo -e ${green}'soccer_dery passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_dery'$cases${reset}
        exit 0
    fi

    if diff data/soccer_dermag.txt data/ref_output/soccer_dermag.txt; then
        echo -e ${green}'soccer_dermag passed'${reset}
    else
        echo -e ${red}'WrongAnswer on soccer_dermag'$cases${reset}
        exit 0
    fi
else
    echo -e ${red}"running failed"${reset}
    rm runfiltersTh
    exit 1
fi
echo ''
if time ./runfiltersTh data eiffel; then
    echo -e ${green}"runfilters eiffel success"${reset}
    if diff data/eiffel_blurred.txt data/ref_output/eiffel_blurred.txt; then
        echo -e ${green}'eiffel_blurred passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_blurred'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_derx.txt data/ref_output/eiffel_derx.txt; then
        echo -e ${green}'eiffel_derx passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_derx'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_dery.txt data/ref_output/eiffel_dery.txt; then
        echo -e ${green}'eiffel_dery passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_dery'$cases${reset}
        exit 0
    fi

    if diff data/eiffel_dermag.txt data/ref_output/eiffel_dermag.txt; then
        echo -e ${green}'eiffel_dermag passed'${reset}
    else
        echo -e ${red}'WrongAnswer on eiffel_dermag'$cases${reset}
        exit 0
    fi
else
    echo -e ${red}"running failed"${reset}
    rm runfiltersTh
    exit 1
fi
rm runfiltersTh
rm data/soccer_*.txt
rm data/eiffel_*.txt
echo -e ${green}"runfiltersTh test done\nall tests passed"${reset}
