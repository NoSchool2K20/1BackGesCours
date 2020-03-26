open Query;

type express;
type response;
type handler = (Js.Json.t, response) => unit;
[@bs.send] external get: (express, string, handler) => unit = "";
[@bs.send] external post: (express, string, handler) => unit = "";
[@bs.send] external send: (response, string) => unit = "";
[@bs.send] external listen: (express, int) => unit = "";
[@bs.module] external express: unit => express = "express";

let app = express();
get(app, "/", (_, res) => send(res, "hi"));

get(app, "/hello", (_, res) => send(res, "hello"));

get(app, "/world", (_, res) => send(res, "world"));

post(app, "/cheh/:id", (req, res) => {
    Js.log(decodeQuery(req));
    send(res, "req");
});

listen(app, 9000);
Js.log("listen on port 9000");
