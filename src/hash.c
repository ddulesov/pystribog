#include "module.h"

static PyObject *_Update(pystribogHash *self, PyObject *args);
static PyObject *_Final(pystribogHash *self, PyObject *args);
static PyObject *_HexDigest(pystribogHash *self, PyObject *args);
static PyObject *_Clear(pystribogHash *self, PyObject *args);

static PyObject *getDigestSize(pystribogHash *self, void *unused);
//extern PyObject *VerifyError;

static PyObject *
py_new(PyTypeObject *type, PyObject *args,
        PyObject *keywordArgs)
{
    return type->tp_alloc(type, 0);
}

//return 16byte alignment address of data structure
static GOST34112012Context *
CTX(pystribogHash *self){
    uintptr_t ptr = (uintptr_t) &(self->data[0]);
    if( ptr % 0x10 == 0x00 ){
        return (GOST34112012Context *)ptr;
    }
    ptr+= 0x10 - (ptr % 0x10);
    //printf("CTX %p %p \n", &(self->data[0]), (void*)ptr  );
    return (GOST34112012Context *)ptr;
}

static void 
py_free(pystribogHash *obj)
{
    GOST34112012Context *ctx = CTX( obj );
    GOST34112012Cleanup(ctx);
    Py_TYPE(obj)->tp_free((PyObject*) obj);
}

static int 
py_init(PyObject *self, PyObject *args, PyObject *keywordArgs){
    int dig;
    static char *keywordList[] = { "length" , NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywordArgs, "i", keywordList, &dig))
        return -1;

    if (dig!=256 && dig!=512){
        //raiseError(VerifyError, "uninitialized cms");
        return -1;
    }

    //if (posix_memalign(&CTX, (size_t) 16, sizeof(GOST34112012Context)))
    GOST34112012Context *ctx = CTX( (pystribogHash*) self );

    //printf("address self=%p ctx=%p \n",self, ctx);

    GOST34112012Init(ctx, dig);

    return 0;
}

static PyMethodDef py_methods[] = {
    { "update", (PyCFunction) _Update, METH_VARARGS ,"update hash" },
    { "digest", (PyCFunction) _Final, METH_NOARGS ,"hash diges" },
    { "hexdigest", (PyCFunction) _HexDigest, METH_NOARGS ,"hash digest in hex format" },    
    { "clear", (PyCFunction) _Clear, METH_NOARGS ,"clear hash" },
    { NULL }
};
static PyGetSetDef py_members[] = {
    { "digest_size", (getter) getDigestSize, 0, 0, 0 },
    { NULL }
};

PyTypeObject pystribogPyTypeHash = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "_pystribog.StribogHash",           // tp_name
    sizeof(pystribogHash),              // tp_basicsize
    0,                                  // tp_itemsize
    (destructor) py_free,                // tp_dealloc
    0,                                  // tp_print
    0,                                  // tp_getattr
    0,                                  // tp_setattr
    0,                                  // tp_compare
    0,                                   // tp_repr
    0,                                  // tp_as_number
    0,                                  // tp_as_sequence
    0,                                  // tp_as_mapping
    0,                                  // tp_hash
    0,                                  // tp_call
    0,                                  // tp_str
    0,                                  // tp_getattro
    0,                                  // tp_setattro
    0,                                  // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                 // tp_flags
    0,                                  // tp_doc
    0,                                  // tp_traverse
    0,                                  // tp_clear
    0,                                  // tp_richcompare
    0,                                  // tp_weaklistoffset
    0,                                  // tp_iter
    0,                                  // tp_iternext
    py_methods,                         // tp_methods
    0,                                  // tp_members
    py_members,                                  // tp_getset
    0,                                  // tp_base
    0,                                  // tp_dict
    0,                                  // tp_descr_get
    0,                                  // tp_descr_set
    0,                                  // tp_dictoffset
    py_init,                            // tp_init
    0,                                  // tp_alloc
    py_new,                             // tp_new
    0,                                  // tp_free
    0,                                  // tp_is_gc
    0                                   // tp_bases
};

static PyObject *
_Update(pystribogHash *self, PyObject *args){
    const unsigned char *data=NULL;
    size_t len = 0;

    if (!PyArg_ParseTuple(args, "s#", &data, &len))
        return NULL;
    GOST34112012Context *ctx = CTX( (pystribogHash*)self );

    GOST34112012Update(ctx, data, (size_t) len); 
    Py_RETURN_NONE; 
}

static PyObject *
_Clear(pystribogHash *self, PyObject *args){
    GOST34112012Context *ctx = CTX( self );
    unsigned int dig = ctx->digest_size;
    GOST34112012Cleanup(ctx);

    GOST34112012Init(ctx, dig);
    Py_RETURN_NONE; 
}

static PyObject *
_Final(pystribogHash *self, PyObject *args){
    unsigned char digest[64];

    GOST34112012Context *ctx = CTX( (pystribogHash*)self );
    GOST34112012Final(ctx, &digest[0]);

    PY_RETURN_BUF((const char*)&digest[0], (ctx->digest_size )>>3 );
}

static PyObject *
_HexDigest(pystribogHash *self, PyObject *args){
    unsigned char digest[64];

    GOST34112012Context *ctx = CTX( (pystribogHash*)self );
    GOST34112012Final(ctx, &digest[0]);
    char buf[130];
    char *ptr = buf;

    for(int i=0;i< (ctx->digest_size )>>3 ;i++){
        ptr+=PyOS_snprintf(ptr, sizeof(buf) - (ptr-buf)-1,"%02x", digest[i] );
    }
    *ptr='\0';

    PyObject* ret = PyUnicode_FromStringAndSize(buf, ptr-buf);
    return ret;
}

static PyObject *
getDigestSize(pystribogHash *self, void *unused){
    GOST34112012Context *ctx = CTX( (pystribogHash*)self );
    return PyInt_FromLong((ctx->digest_size )>>3 );
}