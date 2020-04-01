// Help secure Express apps with various HTTP headers : https://helmetjs.github.io/
// Default config is just fine, don't need complex bindings
[@bs.module] external helmet: unit => Express.Middleware.t = "helmet";
// Compress response body https://github.com/expressjs/compression#readme
[@bs.module]
external compression: unit => Express.Middleware.t = "compression";

open Express;

// bs-express lacks http://expressjs.com/en/4x/api.html#express.json
[@bs.module "express"] external json: unit => Middleware.t = "json";

// INSTANCIATE AN EXPRESS APPLICATION
let app = express();

// SETUP MIDDLEWARES
App.use(app, helmet());
App.use(app, compression());
App.use(app, json());
// setup a middelware that log all access at info level - not GDPR compliant :)
App.use(app, Controller.logRequest);

// SETUP ROUTES
App.get(app, ~path="/", Controller.welcome);

App.get(app, ~path="/cours", Controller.Cours.getAll);
//App.post(app, ~path="/cours", Controller.Cours.create);
//
//App.get(app, ~path="/parcours", Controller.Parcours.getAll);
//App.post(app, ~path="/parcours", Controller.Parcours.create);
//
App.get(app, ~path="/module", Controller.Module.getAll);
//App.post(app, ~path="/module", Controller.Module.create);
App.useOnPath(app, ~path="*", Controller.badRessource);
