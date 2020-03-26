type query = {
    name: string
}

type req = {    
    query: query,
    params: string,
    body: string
}

let decodeQuery = json =>
  Json.Decode.({
     json |> field("query", string)
  });
