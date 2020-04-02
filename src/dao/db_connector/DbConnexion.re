module Dbconnexion = {
    let connection =
      KnexConfig.Connection.make(
      ~host="18.220.58.155",
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
