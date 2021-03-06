open JsonWebToken;
open Json_encode;

type tokenRole = {
  email: string,
  userRole: string,
  name : string
};

module Decoder = {
    let decodeToken = token => {
          let jsonFromToken = decode(token);
          Json.Decode.{
            email: jsonFromToken |> field("email", string),
            userRole: jsonFromToken |> field("userRole", string),
            name : jsonFromToken |> field("name", string)
          };
      };

    let verifyPermission = (token, roleToSatisfy) => {
        let user_token = {
          "token" : token
        }
        Js.Promise.(
          Axios.postData("https://noschool-authentication.cleverapps.io/verify", {user_token})
          |> then_((response) => {
            switch response##data {
            | true => {
              let role = decodeToken(token);
              resolve(Js.Array.includes(role.userRole, roleToSatisfy));
            }
            | _ => resolve(false)
            };
          })
          |> catch((error) => {
            Js.log(error);
            resolve(false);
          })
        );
    }
};
