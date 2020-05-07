module Amqp = AmqpConnectionManager;
[@bs.val] external setTimeout: (unit => unit, int) => int = "setTimeout";

let newCourse_qn = "QnewCourse";
let viewCourse_qn = "QviewCourse";

// Create a connetion manager
let amqp_u = "qzscetiz"
let amqp_p = "iLJmX80CVSklfcVeS1NH81AwaHLSikPh"
let amqp_host = "crow.rmq.cloudamqp.com"
let amqp_url = "amqp://"++amqp_u++":"++amqp_p++"@"++amqp_host++"/"++amqp_u
let connection = Amqp.connect([|amqp_url|], ());

Amqp.AmqpConnectionManager.on(
  connection,
  `disconnect(err => Js.Console.error(err)),
)
|> ignore;

Amqp.AmqpConnectionManager.on(
  connection,
  `connect(_ => Js.Console.info("connected!")),
)
|> ignore;

let createContent = (username : string, email : string, content : string, subject : string) => {
    let message = {
          "personalizations":
          [
              {
                  "to":
                  [
                      {
                          "email": email,
                          "name": username
                      }
                  ],
                  "subject": subject
              }
          ],
          "from":
          {
              "email": "admin@noschool2k20.fr",
              "name": "NoReply NoSchool 2K20"
          },
          "content":
          [
              {
                  "type": "text/plain",
                  "value": content
              }
          ]
     }
     message
 };

// Set up a channel listening for messages in the queue QnewCourse.
let channelNewWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "json": true,
      "setup": channel =>
        // `channel` here is a regular amqplib `ConfirmChannel`.
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, newCourse_qn, {"durable": true})
            |> then_(_ => resolve()),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

  // Set up a channel listening for messages in the queue QvewCourse.
let channelViewWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "json": true,
      "setup": channel =>
        // `channel` here is a regular amqplib `ConfirmChannel`.
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, viewCourse_qn, {"durable": true})
            |> then_(_ => resolve()),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

let newCourse = (courseName : string) => {
  Amqp.ChannelWrapper.sendToQueue(
    channelNewWrapper,
    newCourse_qn,
    {"CourseName": courseName},
    Js.Obj.empty(),
  )
  |> Js.Promise.then_(msg => {
       Js.Console.info("Message sent");
       Js.Promise.make((~resolve, ~reject as _) =>
         setTimeout(() => resolve(. msg), 1000) |> ignore
       );
     })
};

let viewCourse = (courseName : string , username : string, email : string) => {
  let content = "Le cours " ++ courseName ++ " vient d'être consulté";
  let subject = "Consultation d'un cours";
  Amqp.ChannelWrapper.sendToQueue(
    channelViewWrapper,
    viewCourse_qn,
    createContent(username, email, content, subject),
    Js.Obj.empty(),
  )
  |> Js.Promise.then_(msg => {
       Js.Console.info("Message sent viewCourse");
       Js.Promise.make((~resolve, ~reject as _) =>
         setTimeout(() => resolve(. msg), 1000) |> ignore
       );
     })
};

