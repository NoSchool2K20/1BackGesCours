open Express;

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
