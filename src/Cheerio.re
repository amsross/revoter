type element;
type selector = (. string) => element;

[@bs.module "cheerio"] external load: string => selector = "load";
[@bs.send] external getVal: element => string = "val";
