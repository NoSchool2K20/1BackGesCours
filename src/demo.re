type express;
type middleware;
type response;
type request('query, 'body) = {
  .
  "query": Js.t('query),
  "body": Js.t('body),
};
type handler('query, 'body) = (request('query, 'body), response) => unit;
[@bs.send] external get: (express, string, handler('query, 'body)) => unit = "";
[@bs.send] external post: (express, string, handler('query, 'body)) => unit = "";
[@bs.send] external send: (response, Js.Json.t) => unit = "";
[@bs.send] external listen: (express, int) => unit = "";
[@bs.module] external express: unit => express = "express";
[@bs.send] external use: (express, middleware) => unit = "use";
[@bs.module "express"] external json: unit => middleware = "json";

let app = express();
app->use(json());

post(app, "/cheh/:id", (req, res) => {
    Doquery.get_info("cours");
    let name = req##query##name -> Belt.Option.getWithDefault("Not Set") // if not set
    Js.log(req);
    Js.log(req##query##name);
    Js.log(req##body);
    send(res, Request.makeSuccessJson());
  },
);

listen(app, 9000);
Js.log("listen on port 9000");