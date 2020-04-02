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