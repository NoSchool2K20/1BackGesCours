type cours = {
    name: string,
    other: string
}

let decodeCours= json =>
  Json.Decode.{
    name: json |> field("start", string),
    other: json |> field("end", string)
  };