# 빌드 디렉토리 지정 (필요에 따라 수정)
BUILD_DIR="build_project"

# CMakeCache.txt에서 PROJECT_NAME 추출
PROJECT_NAME=$(grep '^CMAKE_PROJECT_NAME:STATIC=' "$BUILD_DIR/CMakeCache.txt" | cut -d'=' -f2)

GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"

# 라이브러리가 빌드되었는지 확인
if [ ! -d "build_project" ]; then
    echo "❌ 라이브러리가 빌드되지 않았습니다."
    echo "먼저 ./shell/CMakeBuildProject.sh 를 실행하세요."
    exit 1
fi

if [ "$GENERATOR_TYPE" = "unix" ]; then
    if [ $LOGGING_TYPE -ne 0 ]; then
        echo "---------메모리 누수 검사 실행---------"
        #MallocStackLogging=1 MallocStackLoggingNoCompact=1 "./$BUILD_DIR/$PROJECT_NAME"
        MallocStackLogging=1 leaks --atExit --list -- "./$BUILD_DIR/$PROJECT_NAME"
    else
        echo "---------일반 실행---------"
        "./${BUILD_DIR}/${PROJECT_NAME}"
    fi
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
