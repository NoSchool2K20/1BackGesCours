let create_table = (table_name) => {
    let conn = OwnMysql.createConnection(~host="192.168.99.100", ~port=3306, ~user="root", ~password="admin", ~database="qsi", ());

    OwnMysql.query(conn, "create table cours(name varchar(255));", result => {
    switch (result) {
    | Ok(results) => Js.log(results.results)
    | Error(err) => Js.log(err##message)
    }
    });

    OwnMysql.endConnection(conn);
}

let get_info = (table_name) => {
    let conn = OwnMysql.createConnection(~host="192.168.99.100", ~port=3306, ~user="root", ~password="admin", ~database="qsi", ());

    OwnMysql.query(conn, "SELECT * FROM " ++ table_name, result => {
    switch (result) {
    | Ok(results) => Js.log(results.results)
    | Error(err) => Js.log(err##message)
    }
    });

    OwnMysql.endConnection(conn);
}