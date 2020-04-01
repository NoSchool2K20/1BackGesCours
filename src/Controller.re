open Express;

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
 let createCours =
     PromiseMiddleware.from((_next, req, rep) =>
       Js.Promise.(
         (
             switch (Request.bodyJSON(req)) {
             | None => reject(Failure("INVALID MESSAGE"))
             | Some(reqJson) =>
               switch (
                 reqJson |> Json.Decode.(field("title", optional(string))),
                 reqJson |> Json.Decode.(field("description", optional(string))),
                 reqJson |> Json.Decode.(field("video_url", optional(string))),
                 reqJson |> Json.Decode.(field("modules", optional(string))),
               ) {
               | exception e => reject(e)
               | (Some(title), Some(description), Some(video_url), Some(modules)) =>{
                     DataAccess.Cours.create(
                       title,
                       description,
                       video_url,
                     );
                     DataAccess.Modulecours.create(
                        modules,
                        title
                     );
                 }
               | _ => reject(Failure("INVALID MESSAGE"))
               }
             }
         )
         |> then_(() => {
              rep
              |> Response.setHeader("Status", "201")
              |> Response.sendJson(
                   Json.Encode.(object_([("text", string("Created cours"))])),
                 )
              |> resolve
            })
         |> catch(err => {
              // Sadly no way to get Js.Promise.error message in a safe way
              Js.log(err);

              rep
              |> Response.setHeader("Status", "400")
              |> Response.sendJson(
                   Json.Encode.(
                     object_([
                       (
                         "error",
                         string("INVALID REQUEST OR MISSING MESSAGE FIELD"),
                       ),
                     ])
                   ),
                 )
              |> resolve;
            })
       )
     );
};

module Module = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
     let queryDict = Request.query(req);
                 (
                   switch (queryDict->Js.Dict.get("parcours")) {
                     | Some(c) => {
                     DataAccess.Module.getAllByParcours(c |> Json_decode.string);
                     }
                     | None => DataAccess.Module.getAll()
                   }
                 )
       |> Js.Promise.(
            then_(moduleJson => {
              rep
              |> Response.setHeader("Status", "200")
              |> Response.sendJson(moduleJson)
              |> resolve
            })
          );
     });
 let create =
      PromiseMiddleware.from((_next, req, rep) =>
        Js.Promise.(
          (
              switch (Request.bodyJSON(req)) {
              | None => reject(Failure("INVALID MESSAGE"))
              | Some(reqJson) =>
                switch (
                  reqJson |> Json.Decode.(field("title", optional(string))),
                  reqJson |> Json.Decode.(field("description", optional(string))),
                  reqJson |> Json.Decode.(field("parcours", optional(string))),
                  reqJson |> Json.Decode.(field("niveau", optional(int))),
                ) {
                | exception e => reject(e)
                | (Some(title), Some(description), Some(parcours),  Some(niveau)) =>{
                      DataAccess.Module.create(
                        title,
                        description,
                      );
                      DataAccess.Parcoursmodule.create(
                         parcours,
                         title,
                         niveau,
                      );
                  }
                | _ => reject(Failure("INVALID MESSAGE"))
                }
              }
          )
          |> then_(() => {
               rep
               |> Response.setHeader("Status", "201")
               |> Response.sendJson(
                    Json.Encode.(object_([("text", string("Created module"))])),
                  )
               |> resolve
             })
          |> catch(err => {
               // Sadly no way to get Js.Promise.error message in a safe way
               Js.log(err);

               rep
               |> Response.setHeader("Status", "400")
               |> Response.sendJson(
                    Json.Encode.(
                      object_([
                        (
                          "error",
                          string("INVALID REQUEST OR MISSING MESSAGE FIELD"),
                        ),
                      ])
                    ),
                  )
               |> resolve;
             })
        )
      );
};

module Parcours = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
       DataAccess.Parcours.getAll()
       |> Js.Promise.(
            then_(parcoursJson => {
              rep
              |> Response.setHeader("Status", "200")
              |> Response.sendJson(parcoursJson)
              |> resolve
            })
          );
     });

 let create =
       PromiseMiddleware.from((_next, req, rep) =>
         Js.Promise.(
           (
               switch (Request.bodyJSON(req)) {
               | None => reject(Failure("INVALID MESSAGE"))
               | Some(reqJson) =>
                 switch (
                   reqJson |> Json.Decode.(field("title", optional(string))),
                   reqJson |> Json.Decode.(field("description", optional(string))),
                 ) {
                 | exception e => reject(e)
                 | (Some(title), Some(description)) =>
                       DataAccess.Parcours.create(
                         title,
                         description,
                       );

                 | _ => reject(Failure("INVALID MESSAGE"))
                 }
               }
           )
           |> then_(() => {
                rep
                |> Response.setHeader("Status", "201")
                |> Response.sendJson(
                     Json.Encode.(object_([("text", string("Created parcours"))])),
                   )
                |> resolve
              })
           |> catch(err => {
                // Sadly no way to get Js.Promise.error message in a safe way
                Js.log(err);

                rep
                |> Response.setHeader("Status", "400")
                |> Response.sendJson(
                     Json.Encode.(
                       object_([
                         (
                           "error",
                           string("INVALID REQUEST OR MISSING MESSAGE FIELD"),
                         ),
                       ])
                     ),
                   )
                |> resolve;
              })
         )
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
