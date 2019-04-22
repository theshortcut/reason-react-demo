module Styles = {
  open Css;

  let wrapper =
    style([
      flex(1),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
    ]);
};

[@react.component]
let make = () => {
  let selectedRef = React.useRef(None);
  let onSelectChange = React.Ref.setCurrent(selectedRef);
  let onMouseUp = _ => {
    switch (selectedRef->React.Ref.current) {
    | Some(cardNode) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX(0px) rotate(0deg);transition: transform 200ms ease-in-out;|j},
      );
      onSelectChange(None);
    | _ => ()
    };
  };
  let onMouseMove = event => {
    let clientX = ReactEvent.Mouse.clientX(event);
    switch (selectedRef->React.Ref.current) {
    | Some(cardNode) =>
      let cardNodeObj = ReactDOMRe.domElementToObj(cardNode);
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX(0px) rotate(0deg);|j},
      );
      let clientRect = cardNodeObj##getBoundingClientRect();
      let left: float = clientRect##left;
      let width: float = clientRect##width;
      let center = left +. width /. 2.;
      let translateX = float_of_int(clientX) -. center;
      let rotation = translateX /. 50.;
      cardNodeObj##setAttribute(
        "style",
        {j|transform: translateX($(translateX)px) rotate($(rotation)deg);|j},
      );
      ();
    | _ => ()
    };
  };

  <div className=Styles.wrapper onMouseMove onMouseUp>
    <MenuItem
      imageUrl="https://images.weedmaps.com/original/image_missing.jpg"
      name="Name"
      onSelectChange
    />
  </div>;
};