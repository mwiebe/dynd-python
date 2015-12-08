//
// Copyright (C) 2011-15 DyND Developers
// BSD 2-Clause License, see LICENSE.txt
//

#pragma once

#include <Python.h>

#include <dynd/type.hpp>
#include <dynd/func/callable.hpp>

#include <sstream>

#include "config.hpp"

namespace pydynd {

struct _type_callable_wrapper {
  dynd::ndt::type d;
  dynd::nd::callable c;
  std::string funcname;
};

/**
 * This is the typeobject and struct of w__type_callable from Cython.
 */
extern PyTypeObject *WTypeCallable_Type;
inline bool WTypeCallable_CheckExact(PyObject *obj)
{
  return Py_TYPE(obj) == WTypeCallable_Type;
}
inline bool WTypeCallable_Check(PyObject *obj)
{
  return PyObject_TypeCheck(obj, WTypeCallable_Type);
}
struct WTypeCallable {
  PyObject_HEAD;
  // This is _type_placement_wrapper in Cython-land
  _type_callable_wrapper v;
};
PYDYND_API void init_w__type_callable_typeobject(PyObject *type);
/**
 * This calls the callable in the _type_callable_wrapper, which was
 * returned as a property of a dynd type.
 */
PYDYND_API PyObject *_type_callable_call(const _type_callable_wrapper &ccw,
                                         PyObject *args, PyObject *kwargs);

/**
 * This calls the dynamic __construct__ function attached to the dynd type.
 */
PyObject *call__type_constructor_function(const dynd::ndt::type &dt,
                                          PyObject *args, PyObject *kwargs);

/**
 * Adds all the dynamic names exposed by the dynd type to the provided dict.
 */
void add__type_names_to_dir_dict(const dynd::ndt::type &dt, PyObject *dict);
/**
 * Retrieves a dynamic property from the dynd type as a Python object.
 */
PYDYND_API PyObject *get__type_dynamic_property(const dynd::ndt::type &dt,
                                                PyObject *name);

/**
 * Returns a wrapper for the callable with the dynd type as the first parameter.
 *
 * \param funcname  The callable name.
 * \param c  The callable.
 * \param d  The first parameter for the callable.
 */
PyObject *wrap__type_callable(const std::string &funcname,
                              const dynd::nd::callable &c,
                              const dynd::ndt::type &d);

} // namespace pydynd
