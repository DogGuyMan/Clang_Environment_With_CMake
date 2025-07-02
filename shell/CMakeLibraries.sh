BASE_DIR=$(dirname $0)
GENERATOR_TYPE="$1"

# 라이브러리 Configure 및 Generate
rm -rf build_libraries
echo "🏗️  1단계: 라이브러리 Configure 및 Generate"
echo "-----------------------------------------"
sh "./$BASE_DIR/CMakeConfigureAndGenerateLibraries.sh" "$GENERATOR_TYPE"

if [ $? -ne 0 ]; then
    echo "❌ 라이브러리 Configure 및 Generate 실패"
    exit 1
fi

echo "🏗️  2단계: 라이브러리 빌드"
echo "-----------------------------------------"
sh "./$BASE_DIR/CMakeBuildLibraries.sh" "$GENERATOR_TYPE"

if [ $? -ne 0 ]; then
    echo "❌ 라이브러리 빌드 실패"
    exit 1
fi
