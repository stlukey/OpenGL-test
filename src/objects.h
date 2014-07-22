#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#define NEW(cls, ...)  cls##__new__(__VA_ARGS__);

#define DEL(cls, self) cls##__del__(self)

#endif // _OBJECTS_H_

