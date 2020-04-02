module Dbconnexion = {
    let connection =
      KnexConfig.Connection.make(~filename="./database/backGesCoursdb.sqlite", ());

    let config =
      KnexConfig.make(
        ~client="sqlite3",
        ~connection,
        ~acquireConnectionTimeout=2000,
        (),
      );

    let knex = Knex.make(config);
}
