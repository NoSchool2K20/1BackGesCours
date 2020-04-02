let connection =
  KnexConfig.Connection.make(~filename="./database/yatdb.sqlite", ());

let config =
  KnexConfig.make(
    ~client="sqlite3",
    ~connection,
    ~acquireConnectionTimeout=2000,
    (),
  );

let knex = Knex.make(config);

module Cours = {
  let getAll = () =>
      Js.Promise.(
        knex
        |> Knex.fromTable("cours")
        |> Knex.toPromise
        |> then_(results => {
             Cours.Courslist.fromJson(results)
             |> List.map(cours => {
                  Cours.Cours.make(
                    Cours.Cours.getTitle(cours),
                    Cours.Cours.getDescription(cours),
                    Cours.Cours.getVideoUrl(cours),
                  )
                })
             |> Cours.Courslist.toJson
             |> resolve
           })
      );
  let getAllByModule : string => Js.Promise.t(Js.Json.t) =
    modules =>
        Js.Promise.(
                    knex
                    |> Knex.fromTable("cours")
                    |> Knex.innerJoin("module_cours", "cours.title", "module_cours.cours")
                    |> Knex.where({"module_cours.module": modules})
                    |> Knex.toPromise
                    |> then_(results => {
                         Cours.Courslist.fromJson(results)
                         |> List.map(cours => {
                              Cours.Cours.make(
                                Cours.Cours.getTitle(cours),
                                Cours.Cours.getDescription(cours),
                                Cours.Cours.getVideoUrl(cours),
                              )
                            })
                         |> Cours.Courslist.toJson
                         |> resolve
                       })
                  );

  let create = (title, description, video_url) => {
      let cours = Cours.Cours.make(title, description, video_url);
      Js.Promise.(
        knex
        |> Knex.rawBinding(
             "INSERT INTO cours VALUES ( ? , ? , ?)",
             (
               Cours.Cours.getTitle(cours),
               Cours.Cours.getDescription(cours),
               Cours.Cours.getVideoUrl(cours),
             ),
           )
        |> Knex.toPromise
        |> then_(_ => {resolve()})
      );
    };
};

module Module = {
  let getAll = () =>
      Js.Promise.(
        knex
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
                   knex
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
         knex
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

module Modulecours = {
  let create = (modules, cours) => {
        let moduleCours = Module_cours.Modulecours.make(modules, cours);
        Js.Promise.(
          knex
          |> Knex.rawBinding(
               "INSERT INTO module_cours VALUES ( ? , ? )",
               (
                 Module_cours.Modulecours.getModule(moduleCours),
                 Module_cours.Modulecours.getCours(moduleCours),
               ),
             )
          |> Knex.toPromise
          |> then_(_ => {resolve()})
        );
      };
};

module Parcours = {
  let getAll = () =>
      Js.Promise.(
        knex
        |> Knex.fromTable("parcours")
        |> Knex.toPromise
        |> then_(results => {
             Parcours.Parcourslist.fromJson(results)
             |> List.map(modules => {
                  Parcours.Parcours.make(
                    Parcours.Parcours.getTitle(modules),
                    Parcours.Parcours.getDescription(modules),
                  )
                })
             |> Parcours.Parcourslist.toJson
             |> resolve
           })
      );

  let create = (title, description) => {
          let parcours = Parcours.Parcours.make(title, description);
          Js.Promise.(
            knex
            |> Knex.rawBinding(
                 "INSERT INTO parcours VALUES ( ? , ? )",
                 (
                   Parcours.Parcours.getTitle(parcours),
                   Parcours.Parcours.getDescription(parcours),
                 ),
               )
            |> Knex.toPromise
            |> then_(_ => {resolve()})
          );
        };
};

module Parcoursmodule = {
  let create = (parcours, modules, niveau) => {
          let parcoursModule = Parcours_module.Parcoursmodule.make(parcours, modules, niveau);
          Js.Promise.(
            knex
            |> Knex.rawBinding(
                 "INSERT INTO parcours_module VALUES ( ? , ?,  ? )",
                 (
                   Parcours_module.Parcoursmodule.getParcours(parcoursModule),
                   Parcours_module.Parcoursmodule.getModule(parcoursModule),
                   Parcours_module.Parcoursmodule.getNiveau(parcoursModule),
                 ),
               )
            |> Knex.toPromise
            |> then_(_ => {resolve()})
          );
        };
};


