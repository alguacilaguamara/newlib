#include "libc.h"

char **environ = 0;
weak_alias(environ, ___environ);
weak_alias(environ, _environ);
weak_alias(environ, environ);
