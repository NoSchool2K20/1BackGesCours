open DbConnexion;

module Cours = {
  let getAll = () =>
      Js.Promise.(
        Dbconnexion.knex
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

  let getAllByTitle : string => Js.Promise.t(Js.Json.t) =
      title =>
          Js.Promise.(
                      Dbconnexion.knex
                      |> Knex.fromTable("cours")
                      |> Knex.where({"title": title})
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
                    Dbconnexion.knex
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
        Dbconnexion.knex
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

