module Amqp = AmqpConnectionManager;
[@bs.val] external setTimeout: (unit => unit, int) => int = "setTimeout";

let newCourse_qn = "QnewCourse";
let viewCourse_qn = "QnewCourse";

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

// Send a message with the courseName as payload
let rec newCourse = (courseName : string) => {
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
  /* |> Js.Promise.then_(_ => JS)
  |> Js.Promise.catch(err => {
       Js.Console.error(err);
       Amqp.ChannelWrapper.close(channelWrapper);
       Amqp.AmqpConnectionManager.close(connection);

       Js.Promise.resolve();
     }); */
};

