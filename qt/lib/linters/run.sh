#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

print_header "RUN cppcheck"
check_log "cppcheck project --enable=warning --inconclusive --error-exitcode=0 -I ../* --suppress=missingIncludeSystem" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy ../*.cpp -header-filter=.* -extra-arg=-std=c++11" "Error (?:reading|while processing)"

#print_header "RUN cppcheck"
#check_log "cppcheck --verbose  --error-exitcode=0 * lib/*"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp, ../*.cpp * ../*.h" "Can't open for reading"

print_header "SUCCESS"