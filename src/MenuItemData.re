type menuItem = {
  name: string,
  imageUrl: string,
};

module Decode = {
  let menuItem = json =>
    Json.Decode.{
      name: json |> field("name", string),
      imageUrl: json |> at(["avatar_image", "original_url"], string),
    };

  let response = json =>
    json |> Json.Decode.(at(["data", "menu_items"], array(menuItem)));
};

let menuItemsUrl = "https://api-g.weedmaps.com/discovery/v1/menu_items?include[]=menu_item.listing&page_size=50&sort_by=distance";

let fetchMenuItems = () =>
  Js.Promise.(
    Bs_fetch.fetch(menuItemsUrl)
    |> then_(Bs_fetch.Response.text)
    |> then_(jsonText =>
         resolve(Decode.response(Js.Json.parseExn(jsonText)))
       )
  );