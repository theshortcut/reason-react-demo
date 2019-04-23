module Styles = {
  open Css;

  let wrapper =
    style([
      flex(1),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
    ]);

  let menuItems =
    style([
      boxShadow(~blur=px(3), rgba(0, 0, 0, 0.2)),
      width(rem(18.75)),
      height(rem(21.9375)),
    ]);
};

[@react.component]
let make = (~menuItems) => {
  let selectedRef = React.useRef(None);
  let onSelectChange = React.Ref.setCurrent(selectedRef);
  let onMouseUp = event => {
    let clientX = event->ReactEvent.Mouse.clientX;
    let rootElement = event->ReactEvent.Mouse.currentTarget;
    let width: float = rootElement##getBoundingClientRect()##width;
    let percentage = float_of_int(clientX) /. width *. 2. -. 1.;
    let liked =
      percentage > 0.5
        ? Some(true) : percentage < (-0.5) ? Some(false) : None;
    switch (selectedRef->React.Ref.current, liked) {
    | (Some(cardNode), Some(true)) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX(calc(100vw)) rotate(25deg);transition: transform 200ms ease-in-out;|j},
      );
    | (Some(cardNode), Some(false)) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX(calc(-100vw)) rotate(-25deg);transition: transform 200ms ease-in-out;|j},
      );
    | (Some(cardNode), None) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX(0px) rotate(0deg);transition: transform 200ms ease-in-out;|j},
      );
    | _ => ()
    };
    onSelectChange(None);
  };
  let onMouseMove = event => {
    let clientX = event->ReactEvent.Mouse.clientX;
    let rootElement = event->ReactEvent.Mouse.currentTarget;
    let width: float = rootElement##getBoundingClientRect()##width;
    let percentage = float_of_int(clientX) /. width *. 2. -. 1.;
    switch (selectedRef->React.Ref.current) {
    | Some(cardNode) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      let _attrs =
        cardNodeObj##setAttribute(
          "style",
          {j|transform: translateX(0px) rotate(0deg);|j},
        );
      let clientRect = cardNodeObj##getBoundingClientRect();
      let cardLeft: float = clientRect##left;
      let cardWidth: float = clientRect##width;
      let cardCenter = cardLeft +. cardWidth /. 2.;
      let translateX = float_of_int(clientX) -. cardCenter;
      let rotation = 20. *. percentage;
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX($(translateX)px) rotate($(rotation)deg); box-shadow: 0 3px 6px rgba(0,0,0,0.4);|j},
      );
    | _ => ()
    };
  };

  let menuItemElements =
    switch (menuItems) {
    | Some(menuItems) =>
      ReasonReact.array(
        Array.map(
          (menuItem: MenuItemData.menuItem) =>
            <MenuItem key={menuItem.name} menuItem onSelectChange />,
          menuItems,
        ),
      )
    | None => React.string("Loading...")
    };

  <div className=Styles.wrapper onMouseMove onMouseUp>
    <div className=Styles.menuItems> menuItemElements </div>
  </div>;
};