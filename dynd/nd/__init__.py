from dynd.config import *

from .array import array, asarray, type_of, dshape_of, as_py, view, \
    ones, zeros, empty, full, is_c_contiguous, is_f_contiguous, range, \
    parse_json, squeeze, dtype_of, linspace, fields, ndim_of, as_numpy, overload_assign
from .callable import callable

inf = float('inf')
nan = float('nan')

from .registry import get_published_callables
from . import functional

## This is a hack until we fix the Cython compiler issues
#class json(object):
#    @staticmethod
#    def parse(tp, obj):
#        return _parse(tp, obj)

for key in get_published_callables():
    globals()[key] = get_published_callables()[key]

overload_assign(globals()["assign"])
