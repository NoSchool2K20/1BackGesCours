// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Query = require("./bo/query.bs.js");
var Js_dict = require("bs-platform/lib/js/js_dict.js");
var Express = require("express");

var app = Express();

app.post("/cheh/:id", (function (req, res) {
        console.log(req);
        console.log(Query.decodeQuery(req));
        console.log(Query.decodeParams(req));
        console.log(Query.decodeBody(req));
        Js_dict.get(Query.decodeQuery(req), "name");
        res.send(Query.makeSuccessJson(/* () */0));
        return /* () */0;
      }));

app.listen(9000);

console.log("listen on port 9000");

exports.app = app;
/* app Not a pure module */
