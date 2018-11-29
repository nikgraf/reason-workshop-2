module Styles = {
  open Emotion;

  let list = [%css
    [margin(`auto), maxWidth(`px(632)), margin3(`rem(1.), `auto, `zero)]
  ];

  let preview = [%css
    [
      width(`px(632)),
      height(`px(280)),
      borderRadius(`px(6)),
      marginBottom(`rem(1.)),
      boxShadows([
        (`px(0), `px(2), `px(4), `px(0), `rgba((0, 0, 0, 0.2)), false),
        (
          `px(0),
          `px(0),
          `px(0),
          `px(2000),
          `rgba((255, 255, 255, 0.4)),
          true,
        ),
      ]),
      backgroundSize(`cover),
      backgroundPosition(`keywords((`center, `center))),
      position(`relative),
    ]
  ];

  let headline = [%css [fontSize(`rem(1.5))]];

  let link = [%css [textDecoration(`none), color(`hex("000"))]];

  let content = [%css [padding(`rem(1.))]];

  let description = [%css
    [whiteSpace(`nowrap), overflow(`hidden), textOverflow(`ellipsis)]
  ];

  let filterInput = [%css
    [
      fontSize(`rem(0.8)),
      boxSizing(`borderBox),
      display(`block),
      width(`px(632)),
      padding2(`rem(0.4), `rem(0.4)),
      borderRadius(`px(6)),
      margin(`auto),
      border(`px(1), `solid, `hex("ccc")),
    ]
  ];
};

let s = ReasonReact.string;

type state = {term: string};

type action =
  | UpdateTerm(string)
  | ResetTerm;

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {term: ""},

  reducer: (action, _state) =>
    switch (action) {
    | UpdateTerm(term) => ReasonReact.Update({term: term})
    | ResetTerm => ReasonReact.Update({term: ""})
    },

  render: self => {
    let filteredPlaces =
      Data.places->Belt.List.keep(place =>
        self.state.term
        ->String.lowercase
        ->Js.String.includes(place.name->String.lowercase)
      );

    <div>
      <input
        value={self.state.term}
        placeholder={j|Filter by name …|j}
        onChange={
          event =>
            self.send(UpdateTerm(event->ReactEvent.Form.target##value))
        }
        className=Styles.filterInput
      />
      <ul className=Styles.list>
        {
          filteredPlaces
          ->Array.of_list
          ->Belt.Array.map(place => {
              let imageUrl = place.image.url;
              let id = place.id;
              <li
                key={place.id}
                className=Styles.preview
                style={
                  ReactDOMRe.Style.make(
                    ~backgroundImage={j|url($imageUrl)|j},
                    (),
                  )
                }>
                <a href={j|/place/$id|j} className=Styles.link>
                  <div className=Styles.content>
                    <h2 className=Styles.headline> place.name->s </h2>
                    <p className=Styles.description> place.description->s </p>
                  </div>
                </a>
              </li>;
            })
          ->ReasonReact.array
        }
      </ul>
    </div>;
  },
};
