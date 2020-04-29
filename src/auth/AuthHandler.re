open Express;

type auth = {
    authorization: string
};

let studentHierarchie = [|"Étudiant", "Professeur", "Administrateur"|];
let teacherHierarchie = [|"Professeur", "Administrateur"|];
let adminHierarchie = [|"Administrateur"|];

let decodeToken = (json: option(Js.Json.t)) =>
    switch json {
    | None =>  Json.Decode.{authorization: ""};
    | Some(t) => try(Json.Decode.{ authorization: t |> field("authorization", string)}){
                    | e => Json.Decode.{authorization: ""};
                };
    };


let getToken = req => {
    let headerDict = decodeToken(Request.asJsonObject(req)->Js.Dict.get("headers"));
    if (headerDict.authorization === "") {
      "error";
    } else{
      Js.String.split(" ", headerDict.authorization)[1];
    }
}

let permitionCheck = hierarchie => next => req => rep => {
    let permitionP = Base64Decoder.Decoder.verifyPermission(
      getToken(req),
      hierarchie
    );
    
    Js.Promise.(permitionP 
        |> then_((permition) => {
            switch permition {
            | true => resolve(rep |> next(Next.middleware))
            | false => resolve(rep
                |> Response.status(Unauthorized)
                |> Response.sendJson(Json.Encode.(object_([("error", string("Unauthorized"),),])),));
            };
        })
    );
};

let studentCheck = PromiseMiddleware.from((next, req, rep) => {
  permitionCheck(studentHierarchie, next, req, rep);
});

let profCheck = PromiseMiddleware.from((next, req, rep) => {
  permitionCheck(teacherHierarchie, next, req, rep);
});

let adminCheck = PromiseMiddleware.from((next, req, rep) => {
  permitionCheck(adminHierarchie, next, req, rep);
});
