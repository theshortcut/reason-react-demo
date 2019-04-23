module Styles = {
  open Css;

  let card =
    style([
      display(flexBox),
      flexDirection(column),
      backgroundColor(white),
      borderRadius(rem(0.25)),
      boxShadow(~y=rem(0.125), ~blur=rem(0.75), rgba(0, 0, 0, 0.5)),
      userSelect(none),
      position(absolute),
    ]);

  let image = style([pointerEvents(none)]);
};

[@react.component]
let make = (~imageUrl: string, ~name: string, ~onSelectChange) => {
  let cardRef = React.useRef(Js.Nullable.null);

  let onMouseDown = _ =>
    switch (cardRef->React.Ref.current->Js.Nullable.toOption) {
    | Some(cardNode) => onSelectChange(Some(cardNode))
    | None => onSelectChange(None)
    };

  <div ref={cardRef->ReactDOMRe.Ref.domRef} className=Styles.card onMouseDown>
    <img
      src={j|$imageUrl?auto=format&w=300&h=300&trim=auto&fit=crop&crop=entropy|j}
      className=Styles.image
      alt=name
    />
    <h3> {React.string(name)} </h3>
  </div>;
};