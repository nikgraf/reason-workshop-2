let s = ReasonReact.string;

module Styles = {
  open Emotion;

  let headline = [%css
    [textAlign(`center), margin3(`rem(4.), `zero, `rem(2.))]
  ];

  let footer = [%css
    [
      color(`hex("666")),
      fontSize(`rem(0.6)),
      textAlign(`center),
      margin3(`rem(3.), `zero, `rem(2.)),
    ]
  ];
};

let getPlace = id => Data.places->Belt.List.getBy(place => place.id == id);

type route =
  | Homepage
  | Place(string)
  | NotFound;

type state = {
  route,
  tmp: string,
};

type actions =
  | ShowHomepage
  | ShowPlace(string)
  | ShowNotFound;

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {
    let url = ReasonReact.Router.dangerouslyGetInitialUrl();
    switch (url.path) {
    | [] => {route: Homepage, tmp: ""}
    | ["place", id] => {route: Place(id), tmp: ""}
    | _ => {route: NotFound, tmp: ""}
    };
  },

  reducer: (action, state) =>
    switch (action) {
    | ShowHomepage => ReasonReact.Update({...state, route: Homepage})
    | ShowPlace(id) => ReasonReact.Update({...state, route: Place(id)})
    | ShowNotFound => ReasonReact.Update({...state, route: NotFound})
    },

  didMount: self => {
    let watcherId =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path) {
        | [] => self.send(ShowHomepage)
        | ["place", id] => self.send(ShowPlace(id))
        | _ => self.send(ShowNotFound)
        }
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherId));
  },

  render: self =>
    <div>
      {
        switch (self.state.route) {
        | Homepage =>
          [|
            <h1 className=Styles.headline> "Vienna"->s </h1>,
            <Weather />,
            <Places />,
          |]
          ->ReasonReact.array
        | NotFound => <NotFound />
        | Place(id) =>
          switch (getPlace(id)) {
          | None => <NotFound />
          | Some(place) => <Place place />
          }
        }
      }
      <footer className=Styles.footer>
        <div> "Made by Nik Graf"->s </div>
        <div> "Design inspired by Marius Hauken"->s </div>
      </footer>
    </div>,
};
