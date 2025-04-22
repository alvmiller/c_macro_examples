#include <stdio.h>


#define DO_NOT_OPTIMIZE(variable) *(volatile char *)variable = *(volatile char *)variable


#define ALWAYS_ZERO(x)            \
    do {                          \
        typeof(x) _tmp_ = (x);    \
        if (_tmp_ != 0) exit(-1); \
    } while (0);


#define MAX(x, y) \
    ({ typeof(x) _x = (x); \
       typeof(y) _y = (y); \
       (void)(&_x == &_y); \
       _x > _y ? _x : _y; \
    })

#define MIN(x, y) \
    ({ typeof(x) _x = (x); \
       typeof(y) _y = (y); \
       (void)(&_x == &_y); \
       _x < _y ? _x : _y; \
    })


#define IS_ARAY_TYPE_GEN(var)        \
    _Generic(&(var),                 \
             typeof((var)[0]) **: 0, \
             default: 1)

#define BUILD_BUG_ON_WITH_ZERO(condition) sizeof(struct { unsigned long :-!!(condition); })
#define IS_SAME_TYPE(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))
#define IS_ARRAY_TYPE(var) (!IS_SAME_TYPE((var), &(var)[0]))

#define SHOULD_BE_ARRAY(a) BUILD_BUG_ON_WITH_ZERO(!IS_ARRAY_TYPE(a))
#define GET_ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + SHOULD_BE_ARRAY(arr))


int main()
{
    char array[10] = {};
    int a = 10;
    printf("array size : %zu\n", GET_ARRAY_SIZE(array));
    printf("MIN MAX : %d %d\n", MIN(1,2), MAX(3,4));
    BUILD_BUG_ON_WITH_ZERO(0);
    DO_NOT_OPTIMIZE(&a);
    ALWAYS_ZERO(0);

    return 0;
}
