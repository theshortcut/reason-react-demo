module Styles = {
  open Css;

  let card =
    style([
      display(flexBox),
      flexDirection(column),
      backgroundColor(white),
      borderRadius(rem(0.25)),
      userSelect(none),
      position(absolute),
      width(rem(18.75)),
      overflow(hidden),
    ]);

  let image = style([pointerEvents(none)]);

  let details = style([padding(rem(1.))]);

  let name =
    style([
      fontSize(rem(1.)),
      overflow(hidden),
      textOverflow(ellipsis),
      whiteSpace(nowrap),
    ]);
};

[@react.component]
let make = (~menuItem: MenuItemData.menuItem, ~onSelectChange) => {
  let cardRef = React.useRef(Js.Nullable.null);

  let onMouseDown = _ =>
    switch (cardRef->React.Ref.current->Js.Nullable.toOption) {
    | Some(cardNode) => onSelectChange(Some(cardNode))
    | None => onSelectChange(None)
    };

  <div ref={cardRef->ReactDOMRe.Ref.domRef} className=Styles.card onMouseDown>
    <img
      src={
        menuItem.imageUrl
        ++ "?auto=format&w=300&h=300&trim=auto&fit=crop&crop=entropy"
      }
      className=Styles.image
      alt={menuItem.name}
    />
    <div className=Styles.details>
      <h3 className=Styles.name> {React.string(menuItem.name)} </h3>
    </div>
  </div>;
};