open DbConnexion;

module Parcours = {
  let getAll = () =>
      Js.Promise.(
        Dbconnexion.knex
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
            Dbconnexion.knex
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
