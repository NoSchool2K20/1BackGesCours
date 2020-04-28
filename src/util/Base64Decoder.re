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
        let jsonFromToken = decode(token);
        let role = decodeToken(jsonFromToken)
        role.userRole === roleToSatisfy
    }
};
