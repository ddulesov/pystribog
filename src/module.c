#include "module.h"

static const char PROJECT_NAME[] = "_pystribog";
static const char PROJECT_DOC[] = "stribog GOST hash functions";


/*PyObject *VerifyError;

PyObject* 
raiseError(PyObject *ErrType, const char *message){
    PyErr_SetString(ErrType, message);
    return NULL;
}
*/
// module own method definitions
static PyMethodDef py_methods[] = {
    { NULL, NULL, 0, NULL }        /* Sentinel */
};

#if PY_MAJOR_VERSION > 2

static struct PyModuleDef py_module = {
    PyModuleDef_HEAD_INIT,
    PROJECT_NAME,   /* name of module */
    PROJECT_DOC, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    pystribog_methods,
    /*
    0,  
    0,  
    pymodule_clear,
    0, 
    */
};

#define  INIT_FUNCTION_NAME PyInit__py( void )
#else
#define  INIT_FUNCTION_NAME	init_pystribog( void )
#endif

PyMODINIT_FUNC INIT_FUNCTION_NAME{
    PyObject *m;

#if PY_MAJOR_VERSION > 2    
    m = PyModule_Create(&py_module);
#else
    m = Py_InitModule3(PROJECT_NAME, py_methods, PROJECT_DOC );
#endif
    if (m == NULL){ RET_MODULE; }

    //VerifyError = PyErr_NewException("pystribog.error", NULL, NULL);
    //PY_ADD_TYPE_OBJECT("Error",  VerifyError );

    PY_ADD_INT_CONSTANT("Hash256", 256);
    PY_ADD_INT_CONSTANT("Hash512", 512);

    PY_MAKE_TYPE_READY(&pystribogPyTypeHash);
    PY_ADD_TYPE_OBJECT("StribogHash", &pystribogPyTypeHash);

#if PY_MAJOR_VERSION > 2    
    return m;	
#endif
}