module Styles = {
  open Emotion;

  let headline = [%css
    [textAlign(`center), margin3(`rem(4.), `zero, `rem(2.))]
  ];
};

let component = ReasonReact.statelessComponent(__MODULE__);

let s = ReasonReact.string;

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <h1 className=Styles.headline> "Sorry, couldn't find this page."->s </h1>
    </div>,
};
