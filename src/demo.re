open Query;

type express;
type response;
type handler = (Js.Json.t, response) => unit;
[@bs.send] external get: (express, string, handler) => unit = "";
[@bs.send] external post: (express, string, handler) => unit = "";
[@bs.send] external send: (response, Js.Json.t) => unit = "";
[@bs.send] external listen: (express, int) => unit = "";
[@bs.module] external express: unit => express = "express";

let app = express();

post(app, "/cheh/:id", (req, res) => {
    Js.log(req);
    Js.log(decodeQuery(req));
    Js.log(decodeParams(req));
    Js.log(decodeBody(req));
    let name = decodeQuery(req) -> Js.Dict.get("name");
    send(res, makeSuccessJson());
});

listen(app, 9000);
Js.log("listen on port 9000");
