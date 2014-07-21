#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#define NEW(obj)       obj##__new__()
#define DEL(obj, self) obj##__del__(self)

#endif // _OBJECTS_H_

