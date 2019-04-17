[@bs.deriving abstract]
type error = {
  field: string,
  value: string,
};

[@bs.deriving abstract]
type results = {
  [@bs.optional]
  success: string,
  [@bs.optional]
  errors: Js.Array.t(error),
};

[@bs.deriving abstract]
type response = {results};

[@bs.scope "JSON"] [@bs.val]
external parseResponse: string => response = "parse";
