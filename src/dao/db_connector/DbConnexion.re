[@bs.val] external bdd_host : string = "process.env.BDD_HOST";
[@bs.val] external bdd_user : string = "process.env.BDD_USER";
[@bs.val] external bdd_password : string = "process.env.BDD_PASSWORD";
[@bs.val] external bdd_db_name : string = "process.env.BDD_DB_NAME";

module Dbconnexion = {
    let connection =
      KnexConfig.Connection.make(
      ~host=bdd_host,
      ~user=bdd_user,
      ~password=bdd_password,
      ~database=bdd_db_name,
      ()
      );

    let config =
      KnexConfig.make(
        ~client="mysql2",
        ~version="5.7",
        ~connection,
        ~acquireConnectionTimeout=2000,
        (),
      );

    let knex = Knex.make(config);
}
