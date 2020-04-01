module Modules: {
  type t;
  let make: (string, string) => t;
  let getTitle: t => string;
  let getDescription: t => string;
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = {
    title: string,
    description: string,
  };

  let make = (title, description) => {title, description};

  let getTitle = modules => modules.title;
  let getDescription = modules => modules.description;

  let fromJson = json =>
    Json.Decode.{
      title: json |> field("title", string),
      description: json |> field("description", string),
    };

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = modules =>
    Json.Encode.(
      object_([
        ("title", string(modules.title)),
        ("description", string(modules.description)),
      ])
    );
  let toString = modules => toJson(modules) |> Js.Json.stringify;
};

module Moduleslist: {
  type t = list(Modules.t); // do not overuse abstraction when unecessary
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(Modules.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(Modules.fromJson));

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = moduleslist =>
    Array.of_list(moduleslist)
    |> Array.map(item => Modules.toJson(item))
    |> Json.Encode.jsonArray;
  let toString = moduleslist => toJson(moduleslist) |> Js.Json.stringify;
};
