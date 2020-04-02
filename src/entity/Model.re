module Cours: {
  type t;
  let make: (string, string, string) => t;
  let getTitle: t => string;
  let getDescription: t => string;
  let getVideoUrl: t => string;
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = {
    title: string,
    description: string,
    video_url: string,
  };

  let make = (title, description, video_url) => {title, description, video_url};

  let getTitle = cours => cours.title;
  let getDescription = cours => cours.description;
  let getVideoUrl = cours => cours.video_url;

  let fromJson = json =>
    Json.Decode.{
      title: json |> field("title", string),
      description: json |> field("description", string),
      video_url: json |> field("video_url", string),
    };

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = cours =>
    Json.Encode.(
      object_([
        ("title", string(cours.title)),
        ("description", string(cours.description)),
        ("video_url", string(cours.video_url)),
      ])
    );
  let toString = cours => toJson(cours) |> Js.Json.stringify;
};

module Courslist: {
  type t = list(Cours.t); // do not overuse abstraction when unecessary
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(Cours.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(Cours.fromJson));

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };

  let toJson = courslist =>
    Array.of_list(courslist)
    |> Array.map(item => Cours.toJson(item))
    |> Json.Encode.jsonArray;
  let toString = courslist => toJson(courslist) |> Js.Json.stringify;
};
