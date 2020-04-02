module Dbconnexion = {
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
}
