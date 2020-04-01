module Parcours: {
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

  let getTitle = parcours => parcours.title;
  let getDescription = parcours => parcours.description;

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

  let toJson = parcours =>
    Json.Encode.(
      object_([
        ("title", string(parcours.title)),
        ("description", string(parcours.description)),
      ])
    );
  let toString = parcours => toJson(parcours) |> Js.Json.stringify;
};

module Parcourslist: {
  type t = list(Parcours.t); // do not overuse abstraction when unecessary
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(Parcours.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(Parcours.fromJson));

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = parcourslist =>
    Array.of_list(parcourslist)
    |> Array.map(item => Parcours.toJson(item))
    |> Json.Encode.jsonArray;
  let toString = parcourslist => toJson(parcourslist) |> Js.Json.stringify;
};
