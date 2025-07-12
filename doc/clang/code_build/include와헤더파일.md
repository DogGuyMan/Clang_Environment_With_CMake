```c
#include <queue.h>
#include <circular_queue.h>
#include <vector.h>
```

이렇게 헤더 파일을 include하고 있는데, 이것을 `<libvector>` 처럼 라이브러리로 직접 참조할 수 있는지 묻고 있습니다.

이것은 C/C++의 기본적인 개념에 대한 질문입니다:

1. **#include는 오직 헤더 파일만 포함할 수 있습니다** - 라이브러리 파일(.a, .so, .dll)은 include할 수 없습니다.
2. **라이브러리는 링킹 단계에서 연결됩니다** - CMake의 target_link_libraries()나 컴파일러의 -l 옵션으로 연결
3. **C++ 표준 라이브러리에서 `<vector>` 같은 것은 헤더 파일입니다** - 실제로는 vector 헤더 파일을 include하는 것

사용자가 현재 CMake 프로젝트에서 어떻게 이 라이브러리들을 사용해야 하는지 설명해야 합니다.

먼저 현재 프로젝트 구조를 좀 더 파악해보겠습니다.
</thinking>

아니요, **C/C++에서는 라이브러리 파일(.a, .so, .dll)을 직접 `#include`할 수 없습니다**. `#include`는 오직 **헤더 파일만** 포함할 수 있습니다.

현재 상황을 정리해보겠습니다: ## C/C++에서 라이브러리 사용 방법

### 1. **헤더 파일 vs 라이브러리 파일**

- **헤더 파일 (.h)**: 함수 선언, 구조체 정의, 매크로 등을 포함
- **라이브러리 파일 (.a, .so, .dll)**: 컴파일된 함수 구현체를 포함

### 2. **올바른 사용법**

```c
// ✅ 올바른 방법: 헤더 파일 include
#include <queue.h>          // 헤더 파일
#include <circular_queue.h> // 헤더 파일
#include <vector.h>         // 헤더 파일

// ❌ 잘못된 방법: 라이브러리 직접 include
#include <libqueue>         // 불가능!
#include <libvector>        // 불가능!
```

### 3. **현재 프로젝트에서의 올바른 연결**

현재 CMakeLists.txt에서 이미 올바르게 설정되어 있습니다:

```cmake
# 헤더 파일 경로 설정
include_directories(${LIBRARY_INSTALL_DIR}/include)

# 라이브러리 파일 경로 설정
link_directories(${LIBRARY_INSTALL_DIR}/lib)

# 라이브러리 연결
target_link_libraries(${PROJECT_NAME}
    ${LIBRARY_DEPS}  # linkedlist, vector, stack, queue
)
```

### 4. **전체 과정**

1. **컴파일 시간**: `#include <vector.h>` → 헤더 파일의 내용이 소스에 삽입
2. **링킹 시간**: `target_link_libraries(... vector)` → `libvector.a`와 연결

### 5. **C++ 표준 라이브러리의 경우**

```cpp
#include <vector>  // 이것도 실제로는 헤더 파일입니다!
#include <iostream>
#include <string>
```

C++ 표준 라이브러리의 `<vector>`, `<iostream>` 등도 모두 **헤더 파일**입니다. 다만 확장자가 없을 뿐입니다.

### 결론

**현재 코드가 올바릅니다!** `#include <vector.h>`는 헤더 파일을 포함하는 것이고, 실제 라이브러리 연결은 CMake의 `target_link_libraries()`가 처리합니다. 라이브러리 파일 자체를 `#include`할 수는 없습니다.
