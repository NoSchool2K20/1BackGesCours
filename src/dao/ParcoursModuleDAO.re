open DbConnexion;

module Parcoursmodule = {
  let create = (parcours, modules, niveau) => {
          let parcoursModule = ParcoursModule.Parcoursmodule.make(parcours, modules, niveau);
          Js.Promise.(
            Dbconnexion.knex
            |> Knex.rawBinding(
                 "INSERT INTO parcours_module VALUES ( ? , ?,  ? )",
                 (
                   ParcoursModule.Parcoursmodule.getParcours(parcoursModule),
                   ParcoursModule.Parcoursmodule.getModule(parcoursModule),
                   ParcoursModule.Parcoursmodule.getNiveau(parcoursModule),
                 ),
               )
            |> Knex.toPromise
            |> then_(_ => {resolve()})
          );
        };
};
