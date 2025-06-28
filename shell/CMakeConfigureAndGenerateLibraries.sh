GENERATOR_TYPE="$1"

if [ "$GENERATOR_TYPE" = "unix" ]; then
    echo "📦 라이브러리 Configure 및 Generate 중..."

    # 라이브러리 빌드 디렉터리 생성
    if [ ! -d "build_libraries" ]; then
        mkdir -p build_libraries
    fi

    # 라이브러리 Configure 및 Generate
    cmake -S . --preset unix-makefiles-libraries-debug

    if [ $? -ne 0 ]; then
        echo "❌ 라이브러리 Configure 실패"
        exit 1
    fi
else
    echo "쉘 인자에 반드시 unix 또는 xcode 중 하나를 입력해야 합니다."
    exit 1
fi
