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
             Model.Courslist.fromJson(results)
             |> List.map(cours => {
                  Model.Cours.make(
                    Model.Cours.getTitle(cours),
                    Model.Cours.getDescription(cours),
                    Model.Cours.getVideoUrl(cours),
                  )
                })
             |> Model.Courslist.toJson
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
                         Model.Courslist.fromJson(results)
                         |> List.map(cours => {
                              Model.Cours.make(
                                Model.Cours.getTitle(cours),
                                Model.Cours.getDescription(cours),
                                Model.Cours.getVideoUrl(cours),
                              )
                            })
                         |> Model.Courslist.toJson
                         |> resolve
                       })
                  );
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
};
