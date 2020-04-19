let () = {
  let progress = ref(0.);
  let show_progress = () =>
    Printf.printf("%i%%\n%!", int_of_float(progress^ *. 100.));

  let notification = Luv.Async.init(_ => show_progress()) |> Result.get_ok;

  let rec do_work = (total, n) =>
    if (n >= total) {
      ();
    } else {
      Luv.Time.sleep(1000);
      progress := float_of_int(n + 1) /. float_of_int(total);
      ignore(Luv.Async.send(notification));
      do_work(total, n + 1);
    };

  let finished = _ => {
    Luv.Handle.close(notification, ignore);
    print_endline("Done");
  };

  Luv.Thread_pool.queue_work(() => do_work(3, 0), finished);

  ignore(Luv.Loop.run(): bool);
};
