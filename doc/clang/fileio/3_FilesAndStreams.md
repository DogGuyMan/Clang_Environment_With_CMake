<!--
execution : 실행, 집행, 실시
attach : 연결하다, 붙이다, 첨부하다
by means of: ~을 사용하여, ~의 수단으로
preserved : 보존된
provides access : 접근을 제공하다
appending : 추가하다, 덧붙이다
contents : 내용물, 콘텐츠
current end : 현재 끝
only one of several possibilities : 여러 가능성 중 하나일 뿐
overview : 개요, 개관
may appear : 나타날 수 있다
Exclusive : 독점적인, 독특한, 배타적인, 배제적인, 제외하고
wipes out : 완전히 지우다 (젠존제), 완전히 소멸시키다, 기진맥진하게 되다
wiped off : 사라지다.
get wipped out : 완패하다
awkward : 어색한
take it easier : 더 가볍게 하다.
keep up with : ~을 따라잡다.
-->

# 파일과 스트림

실제 파일에 출력을 쓰려면, `fopen` 함수를 사용하여 파일을 우리 프로그램 실행에 연결해야 합니다.

이것은 파일 시스템에서 "mylog.txt"라는 파일을 열고, logfile 변수를 통해 그 파일에 대한 접근을 제공합니다. 모드 인자 "a"는 파일을 추가 모드로 엽니다: 즉, 파일의 내용이 존재한다면 보존되고, 쓰기는 해당 파일의 현재 끝부분에서 시작됩니다.

파일을 여는 여러 가지 모드가 있습니다; "a"는 여러 가능성 중 하나일 뿐입니다. 표 8.4는 해당 문자열에 나타날 수 있는 문자들의 개요를 담고 있습니다.

|Mode | Memo | File status after `fopen` |
|---|---|---|
| 'a' | Append w | File unmodified; position at end |
| 'w' | Write w | Content of file wiped out, if any |
| 'r' | Read r | File unmodified; position at start |

|Modifier | Memo | Additional property|
|---|---|---|
|'+' | Update rw | Opens file for reading and writing |
|'b' | Binary | Views as a binary file; otherwise a text file |
|'x' | Exclusive | Creates a file for writing if it does not yet exist |

| Combination | Desc |
|---|---|
| ”a” | Creates an empty text file if necessary; open for writing at end-of-file |
| ”w” | Creates an empty text file or wipes out content; open for writing |
| ”r” | Opens an existing text file for reading |
| ”a+” | Creates an empty text file if necessary; open for reading and writing at end-offile |
| ”w+” | Creates an empty text file or wipes out content; open for reading and writing |
| ”r+” | Opens an existing text file for reading and writing at beginning of file |
| ”ab" ”rb" ”wb" ”a+b" ”ab+" ”r+b" ”rb+" ”w+b" ”wb+" | Same as above, but for a binary file instead of a text file |
| ”wx" ”w+x" ”wbx" ”w+bx" ”wb+x" | Same as above, but error if the file exists prior to the call |

## `fopen` vs `freopen` 차이점

### 🔍 `fopen` (File Open)
새로운 파일 스트림을 열고 새로운 FILE 포인터를 반환합니다.

```c
FILE* fopen(const char* filename, const char* mode);

// 사용 예시
FILE* file = fopen("data.txt", "r");
if (file == NULL) {
    printf("파일을 열 수 없습니다\n");
    return -1;
}
// 사용 후
fclose(file);
```

### 🔄 `freopen` (File Reopen)
**기존의 FILE 스트림을 닫고 같은 포인터에 새로운 파일을 연결**합니다.

```c
FILE* freopen(const char* filename, const char* mode, FILE* stream);

// 사용 예시 1: 표준 출력을 파일로 리다이렉션
freopen("output.txt", "w", stdout);
printf("이 출력은 콘솔이 아닌 output.txt 파일에 저장됩니다\n");

// 사용 예시 2: 기존 파일 포인터 재사용
FILE* file = fopen("old.txt", "r");
freopen("new.txt", "w", file);  // 같은 포인터로 다른 파일 열기
```

### 📊 주요 차이점 비교

| 특징 | `fopen` | `freopen` |
|------|---------|-----------|
| **용도** | 새로운 파일 스트림 생성 | 기존 스트림을 다른 파일에 재연결 |
| **반환값** | 새로운 FILE 포인터 | 기존 FILE 포인터 (성공시) 또는 NULL |
| **기존 스트림** | 영향 없음 | 자동으로 닫힘 |
| **주요 사용처** | 일반적인 파일 입출력 | 표준 스트림 리다이렉션 |

### 🎯 `freopen`의 주요 활용 사례

#### 1. 표준 입출력 리다이렉션
```c
// 표준 출력을 파일로 리다이렉션
freopen("log.txt", "w", stdout);
printf("이 메시지는 log.txt에 저장됩니다\n");

// 표준 입력을 파일에서 읽도록 변경
freopen("input.txt", "r", stdin);
int number;
scanf("%d", &number);  // input.txt에서 읽음

// 원래대로 복원 (Linux/Mac)
freopen("/dev/tty", "w", stdout);   // 콘솔로 출력 복원
freopen("/dev/tty", "r", stdin);    // 키보드 입력 복원
```

#### 2. 디버깅 로그 전환
```c
// 디버그 모드에서만 로그 파일에 출력
#ifdef DEBUG
    freopen("debug.log", "w", stderr);
#endif

fprintf(stderr, "디버그 정보: 변수 x = %d\n", x);
```

#### 3. 파일 포인터 재사용
```c
FILE* data_file = fopen("data1.txt", "r");
// data1.txt 처리...

// 같은 포인터로 다른 파일 열기
freopen("data2.txt", "r", data_file);
// data2.txt 처리...

fclose(data_file);  // 한 번만 닫으면 됨
```

### ⚠️ 주의사항

1. **`freopen` 실패 시**: 원래 스트림은 이미 닫혔으므로 사용할 수 없음
2. **포터빌리티**: `/dev/tty`는 Unix/Linux 전용 (Windows에서는 `"CON"` 사용)
3. **버퍼 처리**: `freopen` 전에 `fflush()` 호출 권장

### 💡 실제 사용 예시
```c
#include <stdio.h>

int main() {
    // 원래 stdout 백업 (방법이 복잡함)
    printf("콘솔에 출력\n");

    // 파일로 리다이렉션
    freopen("output.log", "w", stdout);
    printf("파일에 출력\n");

    // 콘솔로 복원
    freopen("/dev/tty", "w", stdout);  // Unix/Linux
    // freopen("CON", "w", stdout);    // Windows
    printf("다시 콘솔에 출력\n");

    return 0;
}
```

## 파일에서 포맷된 데이터 읽기 (`fscanf`)

### 🔍 `fscanf` 함수
`fopen`으로 열은 파일에서 포맷 지정자를 사용하여 데이터를 읽을 수 있습니다.

```c
int fscanf(FILE *stream, const char *format, ...);
```

### 📝 기본 사용법

#### 1. 파일 생성 및 데이터 쓰기
```c
#include <stdio.h>

int main() {
    // 먼저 테스트 데이터 파일 생성
    FILE* write_file = fopen("data.txt", "w");
    if (write_file == NULL) {
        printf("파일 생성 실패\n");
        return -1;
    }

    // 포맷된 데이터 쓰기
    fprintf(write_file, "%d %s %c\n", 25, "Hello", 'A');
    fprintf(write_file, "%d %s %c\n", 30, "World", 'B');
    fprintf(write_file, "%d %s %c\n", 35, "Test", 'C');
    fclose(write_file);

    return 0;
}
```

#### 2. 파일에서 포맷된 데이터 읽기
```c
#include <stdio.h>

int main() {
    FILE* read_file = fopen("data.txt", "r");
    if (read_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    int number;
    char string[100];
    char character;

    // 한 줄씩 읽기
    while (fscanf(read_file, "%d %s %c", &number, string, &character) == 3) {
        printf("읽은 데이터: 숫자=%d, 문자열=%s, 문자=%c\n",
               number, string, character);
    }

    fclose(read_file);
    return 0;
}
```

### 🎯 다양한 포맷 지정자 활용

#### 복합 데이터 읽기 예시
```c
#include <stdio.h>

int main() {
    // 테스트 파일 생성 (복합 데이터)
    FILE* write_file = fopen("complex_data.txt", "w");
    fprintf(write_file, "Name: John Age: 25 Grade: A Salary: 50000.50\n");
    fprintf(write_file, "Name: Alice Age: 30 Grade: B Salary: 60000.75\n");
    fclose(write_file);

    // 파일에서 읽기
    FILE* read_file = fopen("complex_data.txt", "r");
    if (read_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    char name[50];
    int age;
    char grade;
    double salary;

    while (fscanf(read_file, "Name: %s Age: %d Grade: %c Salary: %lf",
                  name, &age, &grade, &salary) == 4) {
        printf("이름: %s, 나이: %d, 등급: %c, 급여: %.2f\n",
               name, age, grade, salary);
    }

    fclose(read_file);
    return 0;
}
```

### 📊 주요 포맷 지정자

| 포맷 | 데이터 타입 | 변수 타입 | 예시 |
|------|-------------|-----------|------|
| `%d` | 정수 | `int*` | `fscanf(file, "%d", &number)` |
| `%s` | 문자열 | `char[]` | `fscanf(file, "%s", string)` |
| `%c` | 문자 | `char*` | `fscanf(file, "%c", &character)` |
| `%f` | 실수 | `float*` | `fscanf(file, "%f", &float_num)` |
| `%lf` | 배정밀도 실수 | `double*` | `fscanf(file, "%lf", &double_num)` |
| `%ld` | 긴 정수 | `long*` | `fscanf(file, "%ld", &long_num)` |
| `%x` | 16진수 | `int*` | `fscanf(file, "%x", &hex_num)` |

### ⚠️ 주의사항

#### 1. 반환값 확인
```c
FILE* file = fopen("data.txt", "r");
int number;
char string[100];
char character;

// fscanf 반환값 = 성공적으로 읽은 항목 수
int items_read = fscanf(file, "%d %s %c", &number, string, &character);

if (items_read == 3) {
    printf("모든 데이터 읽기 성공\n");
} else if (items_read == EOF) {
    printf("파일 끝 또는 에러\n");
} else {
    printf("일부 데이터만 읽음: %d개 항목\n", items_read);
}
```

#### 2. 문자열 버퍼 오버플로우 방지
```c
char string[50];
// 안전한 방법: 최대 길이 지정
fscanf(file, "%49s", string);  // 49자 + null terminator
```

#### 3. 공백 문자 처리
```c
// 공백을 포함한 문자열 읽기
char line[200];
fgets(line, sizeof(line), file);  // 한 줄 전체 읽기

// 또는 스캔셋 사용
char text[100];
fscanf(file, "%[^\n]", text);  // 개행 문자까지 읽기
```

### 💡 실전 예시: CSV 파일 읽기
```c
#include <stdio.h>

int main() {
    // CSV 파일 생성
    FILE* csv_file = fopen("data.csv", "w");
    fprintf(csv_file, "1,John,25,Engineer\n");
    fprintf(csv_file, "2,Alice,30,Manager\n");
    fprintf(csv_file, "3,Bob,28,Developer\n");
    fclose(csv_file);

    // CSV 파일 읽기
    csv_file = fopen("data.csv", "r");
    if (csv_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    int id, age;
    char name[50], job[50];
    char line[256];
    int line_number = 0;

    // 첫 번째 줄(헤더) 건너뛰기
    if (fgets(line, sizeof(line), csv_file) != NULL) {
        printf("헤더: %s", line);
    }

    // 데이터 줄들 처리
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        line_number++;
        line[strcspn(line, "\n")] = '\0';  // 개행 문자 제거

        // CSV 파싱 (간단한 방법)
        char* token;
        char line_copy[256];
        strcpy(line_copy, line);

        id = atoi(strtok(line_copy, ","));
        char* name = strtok(NULL, ",");
        char* dept = strtok(NULL, ",");
        salary = atoi(strtok(NULL, ","));

        printf("직원 %d: ID=%d, 이름=%s, 부서=%s, 급여=%d\n",
               line_number, id, name, dept, salary);
    }

    fclose(csv_file);
    return 0;
}
```

## 파일을 줄 단위로 읽어 반복 처리하기

### 🔄 방법 1: `fgets` + `sscanf` 조합 (권장)
한 줄씩 읽어서 문자열에서 포맷 파싱하는 방법입니다.

```c
#include <stdio.h>
#include <string.h>

int main() {
    // 테스트 파일 생성
    FILE* write_file = fopen("students.txt", "w");
    fprintf(write_file, "1 김철수 85 A\n");
    fprintf(write_file, "2 이영희 92 A+\n");
    fprintf(write_file, "3 박민수 78 B\n");
    fprintf(write_file, "4 최지은 95 A+\n");
    fclose(write_file);

    // 파일을 줄 단위로 읽기
    FILE* read_file = fopen("students.txt", "r");
    if (read_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    char line[256];  // 한 줄을 저장할 버퍼
    int line_number = 0;

    // 파일 끝까지 한 줄씩 읽기
    while (fgets(line, sizeof(line), read_file) != NULL) {
        line_number++;

        // 줄 끝의 개행 문자 제거
        line[strcspn(line, "\n")] = '\0';

        // 읽은 줄에서 데이터 파싱
        int id, score;
        char name[50], grade[10];

        int parsed = sscanf(line, "%d %s %d %s", &id, name, &score, grade);
        if (parsed == 4) {
            printf("라인 %d: ID=%d, 이름=%s, 점수=%d, 등급=%s\n",
                   line_number, id, name, score, grade);
        } else {
            printf("라인 %d: 파싱 실패 - %s\n", line_number, line);
        }
    }

    fclose(read_file);
    return 0;
}
```

### 🔄 방법 2: `fscanf`를 for loop에서 직접 사용
파일 크기를 미리 알고 있을 때 사용할 수 있습니다.

```c
#include <stdio.h>

// 파일의 줄 수를 세는 함수
int count_lines(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return -1;

    int lines = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') lines++;
    }
    fclose(file);
    return lines;
}

int main() {
    // 테스트 파일 생성
    FILE* write_file = fopen("data.txt", "w");
    fprintf(write_file, "100 Hello A\n");
    fprintf(write_file, "200 World B\n");
    fprintf(write_file, "300 Test C\n");
    fclose(write_file);

    // 줄 수 계산
    int total_lines = count_lines("data.txt");
    printf("총 %d줄이 있습니다.\n", total_lines);

    // 파일 열기
    FILE* read_file = fopen("data.txt", "r");
    if (read_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    // for loop로 각 줄 처리
    for (int i = 0; i < total_lines; i++) {
        int number;
        char string[100];
        char character;

        int result = fscanf(read_file, "%d %s %c", &number, string, &character);
        if (result == 3) {
            printf("줄 %d: 숫자=%d, 문자열=%s, 문자=%c\n",
                   i + 1, number, string, character);
        } else {
            printf("줄 %d: 읽기 실패\n", i + 1);
            break;
        }
    }

    fclose(read_file);
    return 0;
}
```

### 🔄 방법 3: 구조체 배열에 저장하기
모든 데이터를 메모리에 로드해서 처리하는 방법입니다.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int score;
    char grade[10];
} Student;

int main() {
    // 테스트 파일 생성
    FILE* write_file = fopen("class.txt", "w");
    fprintf(write_file, "1001 김철수 85 B+\n");
    fprintf(write_file, "1002 이영희 92 A\n");
    fprintf(write_file, "1003 박민수 78 C+\n");
    fprintf(write_file, "1004 최지은 95 A+\n");
    fprintf(write_file, "1005 정우진 88 B+\n");
    fclose(write_file);

    // 파일 읽기
    FILE* read_file = fopen("class.txt", "r");
    if (read_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    Student students[MAX_LINES];
    char line[256];
    int count = 0;

    // 모든 줄을 읽어서 구조체 배열에 저장
    while (fgets(line, sizeof(line), read_file) != NULL && count < MAX_LINES) {
        line[strcspn(line, "\n")] = '\0';  // 개행 문자 제거

        int parsed = sscanf(line, "%d %s %d %s",
                           &students[count].id,
                           students[count].name,
                           &students[count].score,
                           students[count].grade);

        if (parsed == 4) {
            count++;
        } else {
            printf("잘못된 형식의 줄: %s\n", line);
        }
    }

    fclose(read_file);

    // for loop로 저장된 데이터 처리
    printf("=== 학생 정보 ===\n");
    for (int i = 0; i < count; i++) {
        printf("학번: %d, 이름: %s, 점수: %d, 등급: %s\n",
               students[i].id, students[i].name,
               students[i].score, students[i].grade);
    }

    // 추가 처리 예시: 평균 계산
    double total_score = 0;
    for (int i = 0; i < count; i++) {
        total_score += students[i].score;
    }
    printf("\n평균 점수: %.2f\n", total_score / count);

    return 0;
}
```

### 🔄 방법 4: CSV 파일 처리
쉼표로 구분된 파일을 처리하는 예시입니다.

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // CSV 파일 생성
    FILE* csv_file = fopen("employees.csv", "w");
    fprintf(csv_file, "ID,Name,Department,Salary\n");  // 헤더
    fprintf(csv_file, "101,김철수,개발팀,5000000\n");
    fprintf(csv_file, "102,이영희,마케팅팀,4500000\n");
    fprintf(csv_file, "103,박민수,영업팀,4800000\n");
    fclose(csv_file);

    // CSV 파일 읽기
    csv_file = fopen("employees.csv", "r");
    if (csv_file == NULL) {
        printf("파일 열기 실패\n");
        return -1;
    }

    char line[256];
    int line_number = 0;

    // 첫 번째 줄(헤더) 건너뛰기
    if (fgets(line, sizeof(line), csv_file) != NULL) {
        printf("헤더: %s", line);
    }

    // 데이터 줄들 처리
    while (fgets(line, sizeof(line), csv_file) != NULL) {
        line_number++;
        line[strcspn(line, "\n")] = '\0';  // 개행 문자 제거

        // CSV 파싱 (간단한 방법)
        char* token;
        char line_copy[256];
        strcpy(line_copy, line);

        int id = atoi(strtok(line_copy, ","));
        char* name = strtok(NULL, ",");
        char* dept = strtok(NULL, ",");
        int salary = atoi(strtok(NULL, ","));

        printf("직원 %d: ID=%d, 이름=%s, 부서=%s, 급여=%d\n",
               line_number, id, name, dept, salary);
    }

    fclose(csv_file);
    return 0;
}
```

### 📊 각 방법의 비교

| 방법 | 장점 | 단점 | 사용 상황 |
|------|------|------|-----------|
| `fgets` + `sscanf` | 안전, 유연함 | 약간 복잡 | **일반적 권장** |
| `fscanf` + for | 간단 | 줄 수를 미리 알아야 함 | 고정 크기 파일 |
| 구조체 배열 | 데이터 재사용 가능 | 메모리 사용량 많음 | 작은 파일, 복잡한 처리 |
| CSV 처리 | 표준 형식 | 파싱 복잡 | CSV 형태 데이터 |

### 💡 권장 패턴
```c
FILE* file = fopen("data.txt", "r");
char line[256];
int line_num = 0;

while (fgets(line, sizeof(line), file) != NULL) {
    line_num++;
    line[strcspn(line, "\n")] = '\0';  // 개행 제거

    // 여기서 sscanf로 파싱
    int var1;
    char var2[50];
    if (sscanf(line, "%d %s", &var1, var2) == 2) {
        printf("라인 %d: %d %s\n", line_num, var1, var2);
    }
}
fclose(file);
```

**결론**: `fgets()`로 한 줄씩 읽고 `sscanf()`로 파싱하는 방법이 가장 안전하고 유연합니다! 🚀
