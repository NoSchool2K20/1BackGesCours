open Express;

//module Todos = {
//  let getAll =
//    PromiseMiddleware.from((_next, req, rep) => {
//      let queryDict = Request.query(req);
//      (
//        switch (queryDict->Js.Dict.get("completed")) {
//        | Some(c) =>
//          switch (c |> Json.Decode.string |> bool_of_string_opt) {
//          | Some(cfilter) => DataAccess.Todos.getByCompletness(cfilter)
//          | None => DataAccess.Todos.getAll()
//          }
//        | None => DataAccess.Todos.getAll()
//        }
//      )
//      |> Js.Promise.(
//           then_(todoJson => {
//             rep
//             |> Response.setHeader("Status", "200")
//             |> Response.sendJson(todoJson)
//             |> resolve
//           })
//         );
//    });
//
//  let get =
//    PromiseMiddleware.from((_next, req, rep) =>
//      switch (Request.params(req)->Js.Dict.get("id")) {
//      | None => rep |> Response.sendStatus(BadRequest) |> Js.Promise.resolve
//      | Some(id) =>
//        id
//        |> Json.Decode.string
//        |> DataAccess.Todos.getById
//        |> Js.Promise.(
//             then_(todoJson => {
//               rep
//               |> Response.setHeader("Status", "200")
//               |> Response.sendJson(todoJson)
//               |> resolve
//             })
//           )
//      }
//    );
//
//  let update =
//    PromiseMiddleware.from((_next, req, rep) =>
//      Js.Promise.(
//        (
//          switch (Request.params(req)->Js.Dict.get("id")) {
//          | None => reject(Failure("INVALID MESSAGE"))
//          | Some(id) =>
//            switch (Request.bodyJSON(req)) {
//            | None => reject(Failure("INVALID MESSAGE"))
//            | Some(reqJson) =>
//              switch (
//                reqJson |> Json.Decode.(field("MESSAGE", optional(string))),
//                reqJson |> Json.Decode.(field("COMPLETED", optional(bool))),
//              ) {
//              | exception e => reject(e)
//              | (Some(msg), Some(isCompleted)) =>
//                DataAccess.Todos.update(
//                  Json.Decode.string(id),
//                  msg,
//                  isCompleted,
//                )
//              | _ => reject(Failure("INVALID MESSAGE"))
//              }
//            }
//          }
//        )
//        |> then_(() => {
//             rep
//             |> Response.setHeader("Status", "201")
//             |> Response.sendJson(
//                  Json.Encode.(object_([("text", string("Updated todo"))])),
//                )
//             |> resolve
//           })
//        |> catch(err => {
//             // Sadly no way to get Js.Promise.error message in a safe way
//             Js.log(err);
//
//             rep
//             |> Response.setHeader("Status", "400")
//             |> Response.sendJson(
//                  Json.Encode.(
//                    object_([
//                      (
//                        "error",
//                        string("INVALID REQUEST OR MISSING MESSAGE FIELD"),
//                      ),
//                    ])
//                  ),
//                )
//             |> resolve;
//           })
//      )
//    );
//
//  let create =
//    PromiseMiddleware.from((_next, req, rep) =>
//      Js.Promise.(
//        (
//          switch (Request.bodyJSON(req)) {
//          | None => reject(Failure("INVALID REQUEST"))
//          | Some(reqJson) =>
//            switch (
//              reqJson |> Json.Decode.(field("MESSAGE", optional(string)))
//            ) {
//            | exception e => reject(e)
//            | None => reject(Failure("INVALID MESSAGE"))
//            | Some(msg) => DataAccess.Todos.create(msg)
//            }
//          }
//        )
//        |> then_(() => {
//             rep
//             |> Response.setHeader("Status", "201")
//             |> Response.sendJson(
//                  Json.Encode.(object_([("text", string("Created todo"))])),
//                )
//             |> resolve
//           })
//        |> catch(err => {
//             // Sadly no way to get Js.Promise.error is an abstract type, we have no way to get its message in a safe way
//             Js.log(err);
//             rep
//             |> Response.setHeader("Status", "400")
//             |> Response.sendJson(
//                  Json.Encode.(
//                    object_([
//                      (
//                        "error",
//                        string("INVALID REQUEST OR MISSING MESSAGE FIELD"),
//                      ),
//                    ])
//                  ),
//                )
//             |> resolve;
//           })
//      )
//    );
//};

module Cours = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
      let queryDict = Request.query(req);
            (
              switch (queryDict->Js.Dict.get("module")) {
                | Some(c) => {
                DataAccess.Cours.getAllByModule(c |> Json_decode.string);
                }
                | None => DataAccess.Cours.getAll()
              }
            )
       |> Js.Promise.(
            then_(coursJson => {
              rep
              |> Response.setHeader("Status", "200")
              |> Response.sendJson(coursJson)
              |> resolve
            })
          );
     });
};

module Module = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
       DataAccess.Module.getAll()
       |> Js.Promise.(
            then_(moduleJson => {
              rep
              |> Response.setHeader("Status", "200")
              |> Response.sendJson(moduleJson)
              |> resolve
            })
          );
     });

 let getAllByModule =
     PromiseMiddleware.from((_next, req, rep) =>
       switch (Request.params(req)->Js.Dict.get("module")) {
       | None => rep |> Response.sendStatus(BadRequest) |> Js.Promise.resolve
       | Some(modules) =>
         modules
         |> Json.Decode.string
         |> DataAccess.Cours.getAllByModule
         |> Js.Promise.(
              then_(coursJson => {
                rep
                |> Response.setHeader("Status", "200")
                |> Response.sendJson(coursJson)
                |> resolve
              })
            )
       }
     );
};

let welcome =
  Middleware.from((_next, _req) => {
    Json.Encode.(
      object_([("text", string("Welcome to 1BackGesCours API"))])
    )
    |> Response.sendJson
  });

let logRequest =
  Middleware.from((next, req) => {
    Request.ip(req)
    ++ " "
    ++ Request.methodRaw(req)
    ++ " ressource "
    ++ Request.path(req)
    |> Logger.info;
    next(Next.middleware);
  });

let badRessource =
  Middleware.from((_next, _req, rep) =>
    rep |> Response.sendStatus(NotFound)
  );
