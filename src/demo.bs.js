// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var Query = require("./bo/query.bs.js");
var Express = require("express");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

var app = Express();

app.use(Express.json());

app.post("/cheh/:id", (function (req, res) {
        Belt_Option.getWithDefault(req.query.name, "Not Set");
        console.log(req);
        console.log(req.query.name);
        console.log(req.body);
        res.send(Query.makeSuccessJson(/* () */0));
        return /* () */0;
      }));

app.listen(9000);

console.log("listen on port 9000");

exports.app = app;
/* app Not a pure module */
