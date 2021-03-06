open Express;

type auth = {
  authorization: string
};

module Cours = {

 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
      let queryDict = Request.query(req);
      let token = Base64Decoder.Decoder.decodeToken(AuthHandler.getToken(req));
            (
              switch (queryDict->Js.Dict.get("module")) {
                | Some(c) => {
                CoursDAO.Cours.getAllByModule(c |> Json_decode.string);
                }
                | None => switch (queryDict->Js.Dict.get("title")) {
                                          | Some(c) => {
                                          RabbitMQ.viewCourse(c |> Json_decode.string, token.name, token.email);
                                          CoursDAO.Cours.getAllByTitle(c |> Json_decode.string);
                                          }
                                          | None => CoursDAO.Cours.getAll()
                                        }
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
     PromiseMiddleware.from((_next, req, rep) => {
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
                     ignore{
                         CoursDAO.Cours.create(
                           title,
                           description,
                           video_url,
                         );
                     }
                     ignore{
                      RabbitMQ.newCourse(title);
                     }
                     ModuleCoursDAO.Modulecours.create(
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
                   Json.Encode.(object_([("success", string("Created cours"))])),
                 )
              |> resolve
            })
         |> catch(err => {
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
     });
};
