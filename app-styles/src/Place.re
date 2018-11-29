let component = ReasonReact.statelessComponent(__MODULE__);

let s = ReasonReact.string;

let make = (~place: Data.place, _children) => {
  ...component,
  render: _self => <div> <h2> place.name->s </h2> </div>,
};
