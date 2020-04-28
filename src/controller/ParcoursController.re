open Express;

module Parcours = {
 let getAll =
      PromiseMiddleware.from((_next, req, rep) => {
      let permission = Base64Decoder.Decoder.verifyPermission("eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6InZhbGVudGludGFydGFyZTU5QGdtYWlsLmNvbSIsInBzZXVkbyI6InRlYW0xIiwibmFtZSI6InRlc3QiLCJzdXJuYW1lIjoidGVzdCIsInVzZXJSb2xlIjoiTm91dmVhdSIsImlhdCI6MTU4Nzk2OTg5OCwiZXhwIjoxNTg4MjI5MDk4fQ.8lg_WPv9HQDKq8zIPDyBfWRZKx_Hr4IDnf12MxSd2Ic", "Nouveau");
      Js.Promise.(
                  (
                    switch (permission) {
                      | true => ParcoursDAO.Parcours.getAll()
                      | false => reject(Failure("INVALID PERMISSION"))
                    }
                  )
        |> then_(parcoursJson => {
               rep
               |> Response.setHeader("Status", "200")
               |> Response.sendJson(parcoursJson)
               |> resolve
             })
        |> catch(err => {
                        // Sadly no way to get Js.Promise.error message in a safe way
                        Js.log(err);

                        rep
                        |> Response.setHeader("Status", "401")
                        |> Response.sendJson(
                             Json.Encode.(
                               object_([
                                 (
                                   "error",
                                   string("INVALID PERMISSION"),
                                 ),
                               ])
                             ),
                           )
                        |> resolve;
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
                       ParcoursDAO.Parcours.create(
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
