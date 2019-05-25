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
#include "process.h"
%}
