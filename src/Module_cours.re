module Modulecours: {
  type t;
  let make: (string, string) => t;
  let getModule: t => string;
  let getCours: t => string;
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = {
    modules: string,
    cours: string,
  };

  let make = (modules, cours) => {modules, cours};

  let getModule = modulecours => modulecours.modules;
  let getCours = modulecours => modulecours.cours;

  let fromJson = json =>
    Json.Decode.{
      modules: json |> field("module", string),
      cours: json |> field("cours", string),
    };

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = modulecours =>
    Json.Encode.(
      object_([
        ("module", string(modulecours.modules)),
        ("cours", string(modulecours.cours)),
      ])
    );
  let toString = modulecours => toJson(modulecours) |> Js.Json.stringify;
};

module Modulescourslist: {
  type t = list(Modulecours.t); // do not overuse abstraction when unecessary
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(Modulecours.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(Modulecours.fromJson));

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = modulescourslist =>
    Array.of_list(modulescourslist)
    |> Array.map(item => Modulecours.toJson(item))
    |> Json.Encode.jsonArray;
  let toString = modulescourslist => toJson(modulescourslist) |> Js.Json.stringify;
};
