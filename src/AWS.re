module Context = {
  type t;
};

module Event = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional]
    headers: Js.Dict.t(string),
  };
};

module Result = {
  [@bs.deriving abstract]
  type t = {
    body: string,
    headers: Js.Dict.t(Js.Json.t),
    statusCode: int,
  };

  let make = (~body, ~statusCode) =>
    t(
      ~body,
      ~statusCode,
      ~headers=
        Js.Dict.fromList([
          ("Access-Control-Allow-Origin", Js.Json.string("*")),
          ("Access-Control-Allow-Credentials", Js.Json.boolean(true)),
        ]),
    );

  let ok = make(~statusCode=200);
  let error = make(~statusCode=500);
};

type handler = (Event.t, Context.t) => Future.t(Result.t);
