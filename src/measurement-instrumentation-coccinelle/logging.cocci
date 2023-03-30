@@
@@
  #include ...
+ #include "logging.h"

@@
identifier fun;
@@
fun (...)
{
+   LOG_CALL (fun);
    <...
+   LOG_RETURN (fun);
    return ...;
    ...>
+   LOG_RETURN (fun);
}
