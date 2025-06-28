#!/bin/bash

# ─── 프로젝트 빌드 스크립트 ──────────────────────────
# 이 스크립트는 미리 빌드된 라이브러리를 사용하여 프로젝트를 빌드합니다.

echo "========================================="
echo "       프로젝트 빌드 시작"
echo "========================================="

# 첫 번째 인자를 받아옵니다.
GENERATOR_TYPE="$1"
LOGGING_TYPE="$2"

if [ -z "$GENERATOR_TYPE" ]; then
    GENERATOR_TYPE="unix"
fi

if [ -z "$LOGGING_TYPE" ]; then
    LOGGING_TYPE=0
fi

# 라이브러리가 빌드되었는지 확인
if [ ! -d "build_libraries/install" ]; then
    echo "❌ 라이브러리가 빌드되지 않았습니다."
    echo "먼저 ./shell/CMakeBuildLibraries.sh 를 실행하세요."
    exit 1
fi

if [ "$GENERATOR_TYPE" = "unix" ]; then
    echo "🔨 프로젝트 빌드 중..."
    cmake --build build_project

    if [ "$LOGGING_TYPE" -ne 0 ]; then
        echo "🔍 메모리 누수 검사와 함께 프로젝트 실행 중..."
        sh "./shell/CMakeExecute.sh" "$GENERATOR_TYPE" 1
    else
        echo "🔨 프로젝트 일반 실행중 중..."
        sh "./shell/CMakeExecute.sh" "$GENERATOR_TYPE" 0
    fi

    if [ $? -ne 0 ]; then
        echo "❌ 프로젝트 빌드 실패"
        exit 1
    fi

    echo "✅ 프로젝트 빌드 완료!"

else
    echo "❌ 지원하지 않는 생성기 타입: $GENERATOR_TYPE"
    echo "사용법: ./CMakeBuildProject.sh [unix] [0|1]"
    echo "  - 두 번째 인자: 0=일반 실행, 1=메모리 누수 검사"
    exit 1
fi

echo "========================================="
echo "     프로젝트 빌드 프로세스 완료"
echo "========================================="
