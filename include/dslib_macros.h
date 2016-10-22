#pragma once

#ifndef DSLIB_TYPE
#error Please define DSLIB_TYPE!
#endif

#define FUNCTION_PASTER(ds, name, type) dslib_ ## ds ## _ ## type ## _ ## name
#define FUNCTION_EVALUATOR(ds, name, type) FUNCTION_PASTER(ds, name, type)
#define DSLIB_FUNCTION(ds, name) FUNCTION_EVALUATOR(ds, name, DSLIB_TYPE)

#define TYPE_PASTER(ds, type) dslib_ ## ds ## _ ## type
#define TYPE_EVALUATOR(ds, type) TYPE_PASTER(ds, type)


