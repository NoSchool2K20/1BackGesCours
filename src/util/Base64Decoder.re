open JsonWebToken;
open Json_encode;

type tokenRole = {
  userRole: string
};

module Decoder = {
    let decodeToken = json =>
      Json.Decode.{
        userRole: json |> field("userRole", string)
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
              let jsonFromToken = decode(token);
              let role = decodeToken(jsonFromToken);
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
