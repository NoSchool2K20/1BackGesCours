open Express;

module Amqp = ConnectionAmqp;

let queue_name = "QnewCourse" ;

let amqp_u = "qzscetiz"
let amqp_p = "iLJmX80CVSklfcVeS1NH81AwaHLSikPh"
let amqp_host = "crow.rmq.cloudamqp.com"
let amqp_url = "amqp://"++amqp_u++":"++amqp_p++"@"++amqp_host++"/"++amqp_u

// Create a connetion manager
let connection = Amqp.connect([|amqp_url|], ());

let channelWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "json": true,
      "setup": channel =>
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, queue_name, {"durable": true})
            |> then_(_ => resolve()),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

module Cours = {
 let getAll =
     PromiseMiddleware.from((_next, req, rep) => {
      let queryDict = Request.query(req);
            (
              switch (queryDict->Js.Dict.get("module")) {
                | Some(c) => {
                CoursDAO.Cours.getAllByModule(c |> Json_decode.string);
                }
                | None => CoursDAO.Cours.getAll()
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
          Amqp.ChannelWrapper.sendToQueue(
            channelWrapper,
            queue_name,
            {"time": Js.Date.now()},
            Js.Obj.empty(),
          )
          |> Js.Promise.then_(msg => {
               Js.Console.info("Message sent");
               Js.Promise.make((~resolve, ~reject as _) =>
                 setTimeout(() => resolve(. msg), 1000) |> ignore
               );
             })
          |> Js.Promise.then_(_ => sendMessage())
          |> Js.Promise.catch(err => {
               Js.Console.error(err);
               Amqp.ChannelWrapper.close(channelWrapper);
               Amqp.AmqpConnectionManager.close(connection);
        
               Js.Promise.resolve();
             });
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
