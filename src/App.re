module Styles = {
  open Css;

  global("*", [boxSizing(borderBox), margin(px(0)), padding(px(0))]);

  global("html,body", [height(pct(100.))]);

  global(
    "body",
    [
      fontFamily("-apple-system, Helvetica, sans-serif"),
      fontSize(pct(100.)),
    ],
  );

  global(
    "#root",
    [display(flexBox), flexDirection(column), height(pct(100.))],
  );

  let header =
    style([
      backgroundColor(hex("222")),
      boxShadow(~y=rem(0.125), ~blur=rem(0.5), rgba(0, 0, 0, 0.5)),
      borderBottom(px(1), solid, hex("ccc")),
      color(white),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
      height(rem(3.)),
    ]);

  let appTitle = style([fontSize(rem(1.5)), fontWeight(`thin)]);

  let main =
    style([
      backgroundColor(hex("eee")),
      display(flexBox),
      alignItems(center),
      justifyContent(center),
      flex(1),
    ]);
};

[@react.component]
let make = () => {
  <>
    <header className=Styles.header>
      <h1 className=Styles.appTitle> {React.string("Nuggle")} </h1>
    </header>
    <main className=Styles.main>
      {React.string("Content will go here")}
    </main>
  </>;
};