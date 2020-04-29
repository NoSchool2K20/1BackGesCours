open Express;

let studentCheck = PromiseMiddleware.from((next, req, rep) => {
        let permitionP = Base64Decoder.Decoder.verifyPermission(
          "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6InZhbGVudGludGFydGFyZTU5QGdtYWlsLmNvbSIsInBzZXVkbyI6InRlYW0xIiwibmFtZSI6InRlc3QiLCJzdXJuYW1lIjoidGVzdCIsInVzZXJSb2xlIjoiTm91dmVhdSIsImlhdCI6MTU4Nzk2OTg5OCwiZXhwIjoxNTg4MjI5MDk4fQ.8lg_WPv9HQDKq8zIPDyBfWRZKx_Hr4IDnf12MxSd2Ic", 
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
          "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6InZhbGVudGludGFydGFyZTU5QGdtYWlsLmNvbSIsInBzZXVkbyI6InRlYW0xIiwibmFtZSI6InRlc3QiLCJzdXJuYW1lIjoidGVzdCIsInVzZXJSb2xlIjoiTm91dmVhdSIsImlhdCI6MTU4Nzk2OTg5OCwiZXhwIjoxNTg4MjI5MDk4fQ.8lg_WPv9HQDKq8zIPDyBfWRZKx_Hr4IDnf12MxSd2Ic", 
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
          "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJlbWFpbCI6InZhbGVudGludGFydGFyZTU5QGdtYWlsLmNvbSIsInBzZXVkbyI6InRlYW0xIiwibmFtZSI6InRlc3QiLCJzdXJuYW1lIjoidGVzdCIsInVzZXJSb2xlIjoiTm91dmVhdSIsImlhdCI6MTU4Nzk2OTg5OCwiZXhwIjoxNTg4MjI5MDk4fQ.8lg_WPv9HQDKq8zIPDyBfWRZKx_Hr4IDnf12MxSd2Ic", 
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