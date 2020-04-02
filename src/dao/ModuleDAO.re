open DbConnexion;

module Module = {
  let getAll = () =>
      Js.Promise.(
        Dbconnexion.knex
        |> Knex.fromTable("module")
        |> Knex.toPromise
        |> then_(results => {
             Module.Moduleslist.fromJson(results)
             |> List.map(modules => {
                  Module.Modules.make(
                    Module.Modules.getTitle(modules),
                    Module.Modules.getDescription(modules),
                  )
                })
             |> Module.Moduleslist.toJson
             |> resolve
           })
      );

 let getAllByParcours : string => Js.Promise.t(Js.Json.t) =
   parcours =>
       Js.Promise.(
                   Dbconnexion.knex
                   |> Knex.fromTable("module")
                   |> Knex.innerJoin("parcours_module", "module.title", "parcours_module.module")
                   |> Knex.where({"parcours_module.parcours": parcours})
                   |> Knex.orderBy("niveau")
                   |> Knex.toPromise
                   |> then_(results => {
                        Module.Moduleslist.fromJson(results)
                        |> List.map(modules => {
                              Module.Modules.make(
                                 Module.Modules.getTitle(modules),
                                 Module.Modules.getDescription(modules),
                              )
                           })
                        |> Module.Moduleslist.toJson
                        |> resolve
                      })
                 );

 let create = (title, description) => {
       let cours = Module.Modules.make(title, description);
       Js.Promise.(
         Dbconnexion.knex
         |> Knex.rawBinding(
              "INSERT INTO module VALUES ( ? , ? )",
              (
                Module.Modules.getTitle(cours),
                Module.Modules.getDescription(cours),
              ),
            )
         |> Knex.toPromise
         |> then_(_ => {resolve()})
       );
     };
 };
