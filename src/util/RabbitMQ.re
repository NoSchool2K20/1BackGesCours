module Amqp = AmqpConnectionManager;
[@bs.val] external setTimeout: (unit => unit, int) => int = "setTimeout";

let queue_name = "QnewCourse";

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

// Set up a channel listening for messages in the queue.
let channelWrapper =
  Amqp.AmqpConnectionManager.createChannel(
    connection,
    {
      "json": true,
      "setup": channel =>
        // `channel` here is a regular amqplib `ConfirmChannel`.
        Js.Promise.(
          all([|
            Amqp.Channel.assertQueue(channel, queue_name, {"durable": true})
            |> then_(_ => resolve()),
          |])
          |> then_(_ => resolve())
        ),
    },
  );

// Send a message with the courseName as payload
let rec sendMessage = (courseName : string) => {
  Amqp.ChannelWrapper.sendToQueue(
    channelWrapper,
    queue_name,
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

