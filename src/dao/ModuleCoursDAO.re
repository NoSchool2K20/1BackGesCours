open DbConnexion;

module Modulecours = {
  let create = (modules, cours) => {
        let moduleCours = ModuleCours.Modulecours.make(modules, cours);
        Js.Promise.(
          Dbconnexion.knex
          |> Knex.rawBinding(
               "INSERT INTO module_cours VALUES ( ? , ? )",
               (
                 ModuleCours.Modulecours.getModule(moduleCours),
                 ModuleCours.Modulecours.getCours(moduleCours),
               ),
             )
          |> Knex.toPromise
          |> then_(_ => {resolve()})
        );
      };
};
