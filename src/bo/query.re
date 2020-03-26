let decodeQuery = json =>
    Json.Decode.({
        json |> field("query", dict(string));
    });

let decodeParams = json =>
    Json.Decode.({
        json |> field("params", dict(string));
    });
  
let decodeBody = json =>
    Json.Decode.({
        json |> field("bodyText", dict(string));
    });

let makeSuccessJson = () => {
    let json = Js.Dict.empty();
    Js.Dict.set(json, "success", Js.Json.boolean(true));
    Js.Json.object_(json);
  };
  