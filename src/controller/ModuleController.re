open Express;

module Module = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
     let queryDict = Request.query(req);
                 (
                   switch (queryDict->Js.Dict.get("parcours")) {
                     | Some(c) => {
                     ModuleDAO.Module.getAllByParcours(c |> Json_decode.string);
                     }
                     | None => ModuleDAO.Module.getAll()
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
                      ignore{
                          ModuleDAO.Module.create(
                            title,
                            description,
                          );
                      }
                      ParcoursModuleDAO.Parcoursmodule.create(
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
               |> Response.status(BadRequest)
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
