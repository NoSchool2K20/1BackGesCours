module Parcoursmodule: {
  type t;
  let make: (string, string, int) => t;
  let getParcours: t => string;
  let getModule: t => string;
  let getNiveau: t => int;
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = {
    parcours: string,
    modules: string,
    niveau: int,
  };

  let make = (parcours, modules, niveau) => {parcours, modules, niveau};

  let getParcours = parcoursmodule => parcoursmodule.parcours;
  let getModule = parcoursmodule => parcoursmodule.modules;
  let getNiveau = parcoursmodule => parcoursmodule.niveau;

  let fromJson = json =>
    Json.Decode.{
      parcours: json |> field("parcours", string),
      modules: json |> field("module", string),
      niveau: json |> field("niveau", int),
    };

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = parcoursmodule =>
    Json.Encode.(
      object_([
        ("parcours", string(parcoursmodule.parcours)),
        ("module", string(parcoursmodule.modules)),
        ("niveau", string(string_of_int(parcoursmodule.niveau))),
      ])
    );
  let toString = parcoursmodule => toJson(parcoursmodule) |> Js.Json.stringify;
};

module Parcoursmodulelist: {
  type t = list(Parcoursmodule.t); // do not overuse abstraction when unecessary
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(Parcoursmodule.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(Parcoursmodule.fromJson));

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = parcoursmodulelist =>
    Array.of_list(parcoursmodulelist)
    |> Array.map(item => Parcoursmodule.toJson(item))
    |> Json.Encode.jsonArray;
  let toString = parcoursmodulelist => toJson(parcoursmodulelist) |> Js.Json.stringify;
};
