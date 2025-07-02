BASE_DIR=$(dirname $0)
GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"

rm -rf build_project
# 프로젝트 Configure 및 Generate
echo "🚀 3단계: 프로젝트 Configure 및 Generate"
echo "-----------------------------------------"
sh "./$BASE_DIR/CMakeConfigureAndGenerateProject.sh" "$GENERATOR_TYPE" "$LOGGING_TYPE"

# 프로젝트 빌드
echo "🚀 4단계: 프로젝트 빌드"
echo "-----------------------------------------"
sh "./$BASE_DIR/CMakeBuildProject.sh" "$GENERATOR_TYPE" "$LOGGING_TYPE"

if [ $? -ne 0 ]; then
    echo "❌ 프로젝트 빌드 실패"
    exit 1
fi
