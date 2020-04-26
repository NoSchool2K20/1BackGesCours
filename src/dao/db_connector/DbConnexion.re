[@bs.val] external bdd_host : string = "process.env.BDD_HOST";
[@bs.val] external bdd_user : string = "process.env.BDD_USER";
[@bs.val] external bdd_password : string = "process.env.BDD_PASSWORD";
[@bs.val] external bdd_db_name : string = "process.env.BDD_DB_NAME";

module Dbconnexion = {
    let connection =
      KnexConfig.Connection.make(
      ~host="192.168.99.100",
      ~user="root",
      ~password="root",
      ~database="qsi",
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
