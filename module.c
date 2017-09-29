#include "Python.h"
#include "codec.h"

/* List of functions defined in the module */

static PyMethodDef percentcoding_methods[] = {
  {NULL,    NULL}    /* sentinel */
};

PyDoc_STRVAR(module_doc, "Fast percent encoding and decoding (AKA \"url encoding\").");

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "percentcoding.cext",  /* m_name */
  module_doc,            /* m_doc */
  -1,                    /* m_size */
  percentcoding_methods, /* m_methods */
  NULL,                  /* m_reload */
  NULL,                  /* m_traverse */
  NULL,                  /* m_clear */
  NULL,                  /* m_free */
};

/* Initialization function for the module (*must* be called initcext) */

PyMODINIT_FUNC
PyInit_cext(void)
{
  /* Make sure exposed types are subclassable. */

  CodecType.tp_base = &PyBaseObject_Type;
  CodecType.tp_name = "percentcoding.cext";

  /* Finalize the type object including setting type of the new type
   * object; doing it here is required for portability, too. */

  if (PyType_Ready(&CodecType) < 0)
    return NULL;

  /* Create the module and add the functions */

  PyObject* mod = PyModule_Create(&moduledef);
  if (mod == NULL)
    return NULL;

  Py_INCREF(&CodecType);
  PyModule_AddObject(mod, "Codec", (PyObject*)&CodecType);

  return mod;
}

