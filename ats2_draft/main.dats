#include "share/atspre_define.hats"
#include "share/atspre_staload.hats"

(* pyhsieh: Just a replica of C version with external C function calls *)
implement main0() =
  let
    val _ = $extfcall(int, "proc_routine")
  in
    ()
  end


%{
/* Note:
 * The generated C code is by default stored in the directory where compiling
 * command is run. From README's instruction this loaction should be project
 * root directory.
 */
#include "src/headers/process.h"
%}
