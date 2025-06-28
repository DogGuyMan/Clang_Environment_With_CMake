GENERATOR_TYPE="$1"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    cmake --preset unix-makefiles-project-debug
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi