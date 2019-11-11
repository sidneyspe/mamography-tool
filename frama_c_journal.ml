(* Frama-C journal generated at 08:46 the 11/06/2013 *)

exception Unreachable
exception Exception of string

(* Run the user commands *)
let run () =
  File.init_from_cmdline ();
  begin try
    (* exception Sys_error("input_value: bad object") raised on:  *)
    Project.load_all "/home/sidney/workspaceC++/_libSVM_/PDI.cpp";
    raise Unreachable
  with
  | Unreachable as exn -> raise exn
  | exn (* Sys_error("input_value: bad object") *) ->
    (* continuing: *)
    !Db.Slicing.Project.set_project None;
    let p_interactive = Project.create "interactive" in
    Project.set_current ~on:true p_interactive;
    Kernel.Files.set [ "/home/sidney/Dropbox/Lixo/refri.c" ];
    File.init_from_cmdline ();
    Project.set_current ~on:true (Project.from_unique_name "default");
    Project.set_current p_interactive;
    let __ = !Db.Metrics.compute () in
    ()
  end

(* Main *)
let main () =
  Journal.keep_file "frama_c_journal.ml";
  try run ()
  with
  | Unreachable -> Kernel.fatal "Journal reachs an assumed dead code" 
  | Exception s -> Kernel.log "Journal re-raised the exception %S" s
  | exn ->
    Kernel.fatal
      "Journal raised an unexpected exception: %s"
      (Printexc.to_string exn)

(* Registering *)
let main : unit -> unit =
  Dynamic.register
    ~plugin:"Frama_c_journal"
    "main"
    (Datatype.func Datatype.unit Datatype.unit)
    ~journalize:false
    main

(* Hooking *)
let () = Cmdline.run_after_loading_stage main; Cmdline.is_going_to_load ()
