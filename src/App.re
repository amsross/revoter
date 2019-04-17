[@bs.val] [@bs.scope ("process", "env")]
external urlBase: string = "URL_BASE";
[@bs.val] [@bs.scope ("process", "env")]
external urlTown: string = "URL_TOWN";
[@bs.val] [@bs.scope ("process", "env")]
external urlVote: string = "URL_VOTE";
[@bs.val] external encodeURIComponent: string => string = "encodeURIComponent";

let headers_ = [
  ("Accept", "application/json, text/javascript, */*; q=0.01"),
  ("Accept-Encoding", "gzip, deflate, br"),
  ("Accept-Language", "en-US,en;q=0.9"),
  ("Cache-Control", "no-cache"),
  ("Referer", urlBase ++ urlTown),
  ("X-Requested-With", "XMLHttpRequest"),
];

let getKey: string => string =
  body => (Cheerio.load(body))(. "#voteKey")->Cheerio.getVal;

let handleKey: (Request.get, string) => Future.t(Types.response) =
  (get, key) =>
    get(urlVote, [("voteKey", encodeURIComponent(key))])
    |> Future.map(Types.parseResponse);

let run: list((string, string)) => Future.t(string) =
  headers => {
    let get = Request.make(urlBase, List.append(headers, headers_));

    get(urlTown, [])
    |> Future.map(getKey)
    |> Future.flatMap(handleKey(get))
    |> Future.flatMap(response => {
         let results = response->Types.resultsGet;
         Js.Console.log(results);

         Future.resolve(
           switch (results->Types.successGet) {
           | Some(_) => "Your vote was counted"
           | None =>
             switch (results->Types.errorsGet) {
             | Some([||])
             | None => "An unknown error occured"
             | Some(errs) =>
               errs |> Js.Array.map(Types.valueGet) |> Js.Array.joinWith(" ")
             }
           },
         );
       });
  };

let success = body => AWS.Result.ok(~body);

let failure = err => {
  Js.Console.log(err);
  AWS.Result.error(~body="An unknown error occured");
};

let main: AWS.handler =
  (event, _context) => {
    let userAgent =
      event->AWS.Event.headersGet
      |> Js.Option.andThen((. dict) => dict->Js.Dict.get("User-Agent"))
      |> Js.Option.getWithDefault(
           "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.103 Safari/537.36",
         );

    run([("User-Agent", userAgent)])
    |> Future.map(success)
    |> Future.error(failure);
  };
