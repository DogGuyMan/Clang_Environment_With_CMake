BASE_DIR=$(dirname $0)

echo "📋 사용법:"
echo "  전체 빌드: ./shell/CMakeBuildAll.sh [unix] [0|1] [0|1]"
echo "    - 첫번째 인자: 생성기 타입 (unix)"
echo "    - 두번째 인자: 메모리 검사 (0=off, 1=on)"
echo "    - 세번째 인자: 라이브러리 빌드 (0=skip, 1=build)"
echo ""
echo "  라이브러리만: ./shell/CMakeBuildLibraries.sh [unix]"
echo "  프로젝트만:   ./shell/CMakeBuildProject.sh [unix] [0|1]"

echo "========================================="
echo "    전체 빌드 프로세스 시작"
echo "========================================="

GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"
BUILD_LIBRARIES="$3"

if [ -z "$GENERATOR_TYPE" ]; then
    GENERATOR_TYPE="unix"
fi

if [ -z "$LOGGING_TYPE" ]; then
    LOGGING_TYPE=0
fi

if [ -z "$BUILD_LIBRARIES" ]; then
    BUILD_LIBRARIES=1
fi

sh $BASE_DIR/CMakePrepare.sh
if [ "$GENERATOR_TYPE" = "unix" ]; then
    GENERATOR_TYPE="unix"

    # 라이브러리
    sh $BASE_DIR/CMakeLibraries.sh

    # 프로젝트
    sh $BASE_DIR/CMakeProject.sh

    echo ""
    echo "========================================="
    echo "    전체 빌드 프로세스 완료!"
    echo "========================================="
    echo ""

    sh $BASE_DIR/CMakeExecute.sh                    ${GENERATOR_TYPE} ${LOGGING_TYPE} ${BUILD_LIBRARIES}
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
