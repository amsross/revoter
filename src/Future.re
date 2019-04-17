type t('a) = Js.Promise.t('a);

let resolve = Js.Promise.resolve;
let make = Js.Promise.make;

let flatMap = fn => Js.Promise.then_(fn);
let map = fn => Js.Promise.then_(x => resolve(fn(x)));
let error = fn => Js.Promise.catch(x => resolve(fn(x)));
