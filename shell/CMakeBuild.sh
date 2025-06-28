# cmake --build build

# 첫 번째 인자를 받아옵니다.
GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    if [ $LOGGING_TYPE -ne 0 ]; then
        echo "---------메모리 누수 검사---------"
        cmake --build --preset unix-makefiles-project-debug --target run_with_leaks
    else
        echo "---------일반 실행---------"
        cmake --build --preset unix-makefiles-project-debug
    fi
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi