
#ifndef _MODULE_H
#define _MODULE_H

#include <Python.h>
#include <gost3411-2012-core.h>

#define CHECK( e )      if(!(e)){ goto err; }

//PyObject* raiseError(PyObject *ErrType, const char *message);

//#define PY_RETURN_EMPTY  return Py_INCREF( Empty), Empty 
#define PY_RETURN_BUF(ptr, len)  return PyBytes_FromStringAndSize(ptr, len);

#if PY_MAJOR_VERSION > 2
#define   RET_MODULE	return NULL
#else
#define   RET_MODULE    return	
#endif

// define macro for adding integer constants
#define PY_ADD_INT_CONSTANT(name, value) \
    if (PyModule_AddIntConstant(m, name, value) < 0) \
        RET_MODULE;

// define macro for adding type objects
#define PY_ADD_TYPE_OBJECT(name, type) \
    Py_INCREF(type); \
    if (PyModule_AddObject(m, name, (PyObject*) type) < 0) \
        RET_MODULE;

// define macro for and making types ready
#define PY_MAKE_TYPE_READY(type) \
    if (PyType_Ready(type) < 0) \
        RET_MODULE;


//struct definitions
typedef struct pystribogHash pystribogHash;

//python type definitions
extern PyTypeObject pystribogPyTypeHash;

//structs
struct pystribogHash {
    PyObject_HEAD;
    unsigned char data[2 * sizeof(GOST34112012Context) ];
    int dig;
};

#endif