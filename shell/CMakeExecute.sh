# 빌드 디렉토리 지정 (필요에 따라 수정)
BUILD_DIR="./build"

# CMakeCache.txt에서 PROJECT_NAME 추출
PROJECT_NAME=$(grep '^CMAKE_PROJECT_NAME:STATIC=' "$BUILD_DIR/CMakeCache.txt" | cut -d'=' -f2)

GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    if [ $LOGGING_TYPE -ne 0 ]; then
        echo "---------메모리 누수 검사 실행---------"
        MallocStackLogging=1 MallocStackLoggingNoCompact=1 "./build/$PROJECT_NAME"
        # MallocStackLogging=1 leaks --atExit --list -- ./build/Project
    else
        echo "---------일반 실행---------"
        "./build/$PROJECT_NAME"
    fi
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi