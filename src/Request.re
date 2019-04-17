type jar;
type response;
type request;
type callback = (Js.Nullable.t(Js.Exn.t), response, string) => unit;
type get = (string, list((string, string))) => Future.t(string);
type make = (string, list((string, string))) => get;

module Params = {
  [@bs.deriving abstract]
  type t = {
    uri: string,
    qs: Js.Dict.t(string),
  };

  let make = t;
};

module Options = {
  [@bs.deriving abstract]
  type t = {
    jar,
    baseUrl: string,
    headers: Js.Dict.t(string),
    followAllRedirects: bool,
  };

  let make = t;
};

[@bs.send]
external get: (request, Params.t, callback) => Future.t(string) = "get";
[@bs.new] [@bs.module "request"] external jar: unit => jar = "jar";
[@bs.module "request"] external defaults: Options.t => request = "defaults";

let make = (baseUrl, headers) => {
  let req =
    defaults(
      Options.make(
        ~jar=jar(),
        ~baseUrl,
        ~headers=Js.Dict.fromList(headers),
        ~followAllRedirects=true,
      ),
    );

  (uri, qs) => {
    Future.make((~resolve, ~reject as _) =>
      get(req, Params.make(~uri, ~qs=Js.Dict.fromList(qs)), (err, _, body) =>
        switch (Js.Nullable.toOption(err)) {
        | None => resolve(. body) |> ignore
        | Some(err) =>
          switch (Js.Exn.message(err)) {
          | Some(message) => Js.Exn.raiseError(message)
          | None => Js.Exn.raiseError("An unknown error occurred")
          }
        }
      )
      |> ignore
    );
  };
};
