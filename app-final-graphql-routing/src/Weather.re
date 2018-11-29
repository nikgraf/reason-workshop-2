module GetWeather = [%graphql
  {|
    query weather {
      location(place: "Vienna") {
        city
        weather {
          summary
          temperature
        }
      }
    }
  |}
];

module GetWeatherQuery = ReasonApollo.CreateQuery(GetWeather);

let component = ReasonReact.statelessComponent(__MODULE__);

let s = ReasonReact.string;

let make = _children => {
  ...component,
  render: _ =>
    <GetWeatherQuery>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <div> "Loading"->s </div>
             | Error(error) => <div> {s(error##message)} </div>
             | Data(response) =>
               <div>
                 {
                   switch (response##location) {
                   | None => ReasonReact.null
                   | Some(location) =>
                     switch (location##weather) {
                     | None => ReasonReact.null
                     | Some(weather) =>
                       switch (weather##summary) {
                       | None => ReasonReact.null
                       | Some(summary) => <p> summary->s </p>
                       }
                     }
                   }
                 }
               </div>
             }
         }
    </GetWeatherQuery>,
};
