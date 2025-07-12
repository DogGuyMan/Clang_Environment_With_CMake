#### 살짝 매크로같은 느낌이다.
```c
// 일반 함수
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(5, 3);  // 함수 호출 (스택 프레임 생성)
    return 0;
}
```

#### 사용하지 말아야 하는 상황
```c
// ❌ 큰 함수 이러면 엄~~~~~~~청 코드 길이가 길어진다.
static inline void complex_algorithm() {
    // 100줄 이상의 복잡한 코드
}

// ❌ 재귀 함수
static inline int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// ❌ 자주 호출되지 않는 함수
static inline void initialize_once() {
    // 프로그램 시작 시 한 번만 호출
}
```
