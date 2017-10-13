[%bs.raw {|require('./card.css')|}];

let component = ReasonReact.statelessComponent "Card";

let make ::value _ => {
  ...component,
  render: fun _self =>
    if (value === 0) {
      <div className="card" />
    } else {
      <div className=("card card_number_" ^ string_of_int value)>
        (ReasonReact.stringToElement (string_of_int value))
      </div>
    }
};
