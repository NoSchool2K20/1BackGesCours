open Express;

type auth = {
      authorization: string
    };

let decodeToken = (json: option(Js.Json.t)) =>
        switch json {
            | None =>  Json.Decode.{
                        authorization: ""
                      };
            | Some(t) => Json.Decode.{
                         authorization: t |> field("authorization", string)
                       };
        };

let getToken = req => {
     let headerDict = decodeToken(Request.asJsonObject(req)->Js.Dict.get("headers"));
     Js.String.split(" ", headerDict.authorization)[1];
 }

let studentCheck = PromiseMiddleware.from((next, req, rep) => {
        let permitionP = Base64Decoder.Decoder.verifyPermission(
          getToken(req),
          "Étudiant"
        );
        
        Js.Promise.(permitionP 
            |> then_((permition) => {
                switch permition {
                | true => resolve(rep |> next(Next.middleware))
                | false => resolve(rep |> Response.sendStatus(Unauthorized))
                };
            })
        );
        
});

let profCheck = PromiseMiddleware.from((next, req, rep) => {
        let permitionP = Base64Decoder.Decoder.verifyPermission(
          getToken(req),
          "Professeur"
        );
        
        Js.Promise.(permitionP 
            |> then_((permition) => {
                switch permition {
                | true => resolve(rep |> next(Next.middleware))
                | false => resolve(rep |> Response.sendStatus(Unauthorized))
                };
            })
        );
        
});

let adminCheck = PromiseMiddleware.from((next, req, rep) => {
        let permitionP = Base64Decoder.Decoder.verifyPermission(
          getToken(req),
          "Administrateur"
        );

        Js.Promise.(permitionP 
            |> then_((permition) => {
                switch permition {
                | true => resolve(rep |> next(Next.middleware))
                | false => resolve(rep |> Response.sendStatus(Unauthorized))
                };
            })
        );
        
});
