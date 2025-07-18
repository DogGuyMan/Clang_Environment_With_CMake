### 매크로를 사용한 제네릭 팁

#### 선언부와 정의부

```h
#define DEFINE_XXX_TYPE(TYPE, TYPE_NAME) \
XXX.h 내부에 작성되야 할 것

#define IMPLEMENT_XXX_TYPE(TYPE, TYPE_NAME) \
XXX.c 내부에 작성되야 할 것

...

DEFINE_XXX_TYPE(int, Int)
DEFINE_XXX_TYPE(float, Float)
DEFINE_XXX_TYPE(double, Double)
DEFINE_XXX_TYPE(long long, LongLong)
DEFINE_XXX_TYPE(char, Char)
DEFINE_XXX_TYPE(short, Short)
```

1. `typedef int __TYPE__` -> `__TYPE__ -> TYPE`
2. `typedef struct CreateCircularQueue__TYPE_NAME__ CreateCircularQueue__TYPE_NAME__` -> `CreateCircularQueue##TYPE_NAME`
3. `typedef struct CreateCircularQueue__TYPE_NAME__SPSP CreateCircularQueue__TYPE_NAME__SPSP` -> `CreateCircularQueue##TYPE_NAME##`
