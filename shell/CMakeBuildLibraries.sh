#!/bin/bash

# ─── 라이브러리 빌드 스크립트 ──────────────────────────
# 이 스크립트는 라이브러리만 빌드하고 설치합니다.

echo "========================================="
echo "    라이브러리 빌드 및 설치 시작"
echo "========================================="

# 첫 번째 인자를 받아옵니다.
GENERATOR_TYPE="$1"

if [ -z "$GENERATOR_TYPE" ]; then
    GENERATOR_TYPE="unix"
fi

if [ "$GENERATOR_TYPE" = "unix" ]; then
    echo "🔨 라이브러리 빌드 중..."

    # 라이브러리 빌드
    cmake --build build_libraries

    if [ $? -ne 0 ]; then
        echo "❌ 라이브러리 빌드 실패"
        exit 1
    fi

    echo "📋 라이브러리 설치 중..."

    # 라이브러리 설치
    cmake --install build_libraries

    if [ $? -ne 0 ]; then
        echo "❌ 라이브러리 설치 실패"
        exit 1
    fi

    echo "✅ 라이브러리 빌드 및 설치 완료!"
    echo "📁 설치 경로: build_libraries/install/"

else
    echo "❌ 지원하지 않는 생성기 타입: $GENERATOR_TYPE"
    echo "사용법: ./CMakeBuildLibraries.sh [unix]"
    exit 1
fi

echo "========================================="
echo "    라이브러리 빌드 프로세스 완료"
echo "========================================="
