
### **스택 할당된 변수는 함수가 종료되면 소멸됩니다.**
* '절대로 함수 내의 로컬 변수를 리턴하지 않는다.'
* 포인터로 전달해도 변수 자체의 생명주기는 변하지 않습니다.
* 스택 할당 변수의 포인터 반환은 C/C++에서 잠재적인 문제를 야기할 수 있습니다.
* 스택 영역에 할당된 변수는 함수가 종료되면 메모리가 해제되므로,
* 해당 변수의 주소를 반환하면 유효하지 않은 메모리 영역을 가리키는 포인터, 즉 dangling pointer가 됩니다

#### 1. Dangling Pointer:
함수 종료 후 스택 영역에서 해당 변수가 사라지므로,
반환된 포인터를 통해 접근하려는 시도는 정의되지 않은 동작을 유발합니다.
#### 2. 메모리 손상:
반환된 포인터를 통해 다른 데이터가 저장된 스택 영역에 접근하게 되면 데이터 손상이 발생할 수 있습니다.

## 🚨 위험한 코드 예시

````c
// ❌ 위험한 코드 - 댕글링 포인터 생성
int* dangerous_function() {
    int local_var = 42;      // 스택에 할당
    return &local_var;       // ❌ 스택 변수의 주소 반환
}  // 함수 종료 시 local_var 소멸

int main() {
    int* ptr = dangerous_function();
    printf("%d\n", *ptr);    // ❌ 정의되지 않은 동작!
    return 0;
}
````

## 🎯 현재 코드의 문제점

### 1. **TryGetData 함수의 위험성**

````c
static inline bool TryGetData(GENERIC_DATA_TYPE * self_ptr, DATA_TYPE try_data_type, void ** out_data) {
    if(self_ptr == NULL || out_data == NULL) {
        return false;
    }

    if(self_ptr->m_type == try_data_type) {
        *out_data = self_ptr->m_data;  // ⚠️ 이 포인터가 스택을 가리키면 위험!
        return true;
    }

    *out_data = NULL;
    return false;
}
````

### 2. **실제 사용 시 발생할 수 있는 문제**

````c
void example_function() {
    int stack_value = 100;    // 스택에 할당

    GENERIC_DATA_TYPE generic_data = {
        .m_type = TYPE_INT,
        .m_data = &stack_value,  // ❌ 스택 변수 주소 저장
        .m_size = sizeof(int)
    };

    // 다른 함수에서 이 데이터를 사용하려고 시도
    process_generic_data(&generic_data);
}  // ⚠️ stack_value 소멸!

void process_generic_data(GENERIC_DATA_TYPE* data) {
    void* extracted_data;
    if(TryGetData(data, TYPE_INT, &extracted_data)) {
        // ❌ extracted_data가 소멸된 스택 변수를 가리킴!
        int value = *(int*)extracted_data;  // 정의되지 않은 동작
        printf("Value: %d\n", value);
    }
}
````

## 🔧 안전한 대안들

### 1. **힙 할당 사용**

````c
// ✅ 안전한 방법 - 힙 할당
GENERIC_DATA_TYPE create_safe_generic_int(int value) {
    int* heap_value = malloc(sizeof(int));  // 힙에 할당
    *heap_value = value;

    return (GENERIC_DATA_TYPE) {
        .m_type = TYPE_INT,
        .m_data = heap_value,    // ✅ 힙 주소는 안전
        .m_size = sizeof(int)
    };
}

// 사용 후 반드시 해제
void cleanup_generic_data(GENERIC_DATA_TYPE* data) {
    if(data != NULL && data->m_data != NULL) {
        free(data->m_data);
        data->m_data = NULL;
    }
}
````

### 2. **값 복사 방식**

````c
// ✅ 안전한 방법 - 값 복사
bool TryGetDataCopy(GENERIC_DATA_TYPE* self_ptr, DATA_TYPE try_data_type, void* out_buffer, size_t buffer_size) {
    if(self_ptr == NULL || out_buffer == NULL) {
        return false;
    }

    if(self_ptr->m_type == try_data_type) {
        if(buffer_size >= self_ptr->m_size) {
            memcpy(out_buffer, self_ptr->m_data, self_ptr->m_size);  // ✅ 값 복사
            return true;
        }
    }

    return false;
}

// 사용 예시
void safe_usage() {
    GENERIC_DATA_TYPE data = /* ... */;
    int result;

    if(TryGetDataCopy(&data, TYPE_INT, &result, sizeof(int))) {
        printf("Value: %d\n", result);  // ✅ 안전함
    }
}
````

### 3. **메모리 소유권 명시**

````c
// ✅ 메모리 소유권을 명시한 구조체
typedef enum {
    MEMORY_STACK,     // 스택 메모리 (복사 필요)
    MEMORY_HEAP,      // 힙 메모리 (해제 필요)
    MEMORY_STATIC     // 정적 메모리 (해제 불필요)
} MEMORY_OWNERSHIP;

struct GENERIC_DATA_TYPE {
    DATA_TYPE m_type;
    MEMORY_OWNERSHIP m_ownership;  // ✅ 메모리 소유권 명시
    void* m_data;
    size_t m_size;
};

// 안전한 TryGetData
static inline bool TryGetDataSafe(GENERIC_DATA_TYPE* self_ptr, DATA_TYPE try_data_type, void** out_data) {
    if(self_ptr == NULL || out_data == NULL) {
        return false;
    }

    if(self_ptr->m_type == try_data_type) {
        if(self_ptr->m_ownership == MEMORY_STACK) {
            // ⚠️ 스택 메모리는 복사해서 사용하도록 경고
            printf("Warning: Stack memory detected. Copy the data before use.\n");
        }
        *out_data = self_ptr->m_data;
        return true;
    }

    *out_data = NULL;
    return false;
}
````

## 📊 스택 vs 힙 생명주기

| 메모리 타입 | 생명주기 | 함수 종료 후 | 포인터 전달 |
|-------------|----------|--------------|-------------|
| **스택** | 함수 범위 | 소멸 | ❌ 위험 |
| **힙** | 명시적 해제 | 유지 | ✅ 안전 |
| **정적** | 프로그램 종료 | 유지 | ✅ 안전 |
| **전역** | 프로그램 종료 | 유지 | ✅ 안전 |

## 🎯 실제 발생하는 문제

````c
// 실제 테스트 코드
void test_stack_lifetime() {
    GENERIC_DATA_TYPE* data = create_stack_data();  // 스택 변수 포인터 반환

    void* extracted;
    if(TryGetData(data, TYPE_INT, &extracted)) {
        // 이 시점에서 extracted는 이미 소멸된 메모리를 가리킴
        int value = *(int*)extracted;  // 💥 크래시 또는 쓰레기 값
        printf("Value: %d\n", value);
    }
}

GENERIC_DATA_TYPE* create_stack_data() {
    int local = 42;
    static GENERIC_DATA_TYPE data = {
        .m_type = TYPE_INT,
        .m_data = &local,  // ❌ 스택 변수 주소
        .m_size = sizeof(int)
    };
    return &data;
}  // local 변수 소멸!
````

## 📋 결론

**스택 할당된 변수는 함수가 종료되면 반드시 소멸됩니다.** 포인터로 전달해도 변수 자체의 생명주기는 변하지 않으므로:

1. **스택 변수의 주소를 함수 밖으로 전달하지 말 것**
2. **필요하면 힙 할당하거나 값 복사 사용**
3. **메모리 소유권을 명시적으로 관리**
4. **현재 코드에서는 메모리 소유권 필드 추가 권장**

이는 C 프로그래밍에서 가장 흔한 버그 중 하나이므로 반드시 주의해야 합니다! 🚨

----

### 참고
* [#7. [레거시 C++ 가이드] 포인터(Pointer)와 참조자(Reference)](https://tango1202.github.io/legacy-cpp-guide/legacy-cpp-guide-pointer-reference/#:~:text=(%20const%20T&%20%EC%99%80%20%EA%B0%99%EC%9D%B4%20%EC%83%81%EC%88%98%ED%98%95%EC%9C%BC%EB%A1%9C%20%EC%B0%B8%EC%A1%B0%ED%95%98%EB%A9%B4,Getter%20%EC%B0%B8%EA%B3%A0)%ED%95%98%EB%8A%94%20%EB%8A%90%EB%82%8C%EC%9D%84%20%EC%A3%BC%EA%B8%B0%20%EB%95%8C%EB%AC%B8%EC%97%90%2C%20%EC%95%88%EC%93%B0%EC%8B%9C%EB%8A%94%EA%B2%8C%20%EC%A2%8B%EC%8A%B5%EB%8B%88%EB%8B%A4.))
