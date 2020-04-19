// Help secure Express apps with various HTTP headers : https://helmetjs.github.io/
// Default config is just fine, don't need complex bindings
[@bs.module] external helmet: unit => Express.Middleware.t = "helmet";
// Compress response body https://github.com/expressjs/compression#readme
[@bs.module]
external compression: unit => Express.Middleware.t = "compression";

open Express;

// bs-express lacks http://expressjs.com/en/4x/api.html#express.json
[@bs.module "express"] external json: unit => Middleware.t = "json";

[@bs.module] external cors: unit => Express.Middleware.t = "cors";

// INSTANCIATE AN EXPRESS APPLICATION
let app = express();

// SETUP MIDDLEWARES
App.use(app, helmet());
App.use(app, compression());
App.use(app, json());
App.use(app, cors());
// setup a middelware that log all access at info level - not GDPR compliant :)
App.use(app, Controller.logRequest);

// SETUP ROUTES
App.get(app, ~path="/", Controller.welcome);

App.get(app, ~path="/cours", CoursController.Cours.getAll);
App.post(app, ~path="/cours", CoursController.Cours.createCours);

App.get(app, ~path="/parcours", ParcoursController.Parcours.getAll);
App.post(app, ~path="/parcours", ParcoursController.Parcours.create);
//
App.get(app, ~path="/module", ModuleController.Module.getAll);
App.post(app, ~path="/module", ModuleController.Module.create);

App.useOnPath(app, ~path="*", Controller.badRessource);
