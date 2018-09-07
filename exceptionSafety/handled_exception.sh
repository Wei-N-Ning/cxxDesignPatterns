#!/usr/bin/bash

# exceptional P103
# what is a try-block
# a try block is a block of code whose execution will be attempted, 
# followed by a series of one or more handler blocks that can be entered 
# to catch an exception of the appropriate type if one is emitted from 
# the attempted code

# do not mix exception safety and try-catch
# exceptions are just another form of error reporting
# writing error-safe code is not just about where to check return code 
# and handle error conditions

# exception safety is rarely about writing try catch; and the more rarely 
# the better.

# exception safety affects a piece of code's design; 
# it is never just an afterthought that can be retrofitted with a few 
# extra catch statements as if for seasoning 

CXX=${CXX:-c++}

# catch any exception
cat >/tmp/sut/_.cpp <<"EOF"
int main() {
    try {
        throw 42;
    }
    catch (...) {
        return 1;
    }
    return 0;
}
EOF

${CXX} -o /tmp/sut/_ /tmp/sut/_.cpp
/tmp/sut/_ >/dev/null 2>&1
echo $?

# catch exceptions of specific types
cat >/tmp/sut/_handled.cpp <<"EOF"
int main() {
    try {
        throw 42;
    }
    catch (const int& exc) {
        return 42;
    }
    catch (const char*) {
        ;
    }
    return 0;
}
EOF

${CXX} -o /tmp/sut/handled /tmp/sut/_handled.cpp
/tmp/sut/handled >/dev/null 2>&1
echo $?

