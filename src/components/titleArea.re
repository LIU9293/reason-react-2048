let component = ReasonReact.statelessComponent "TitleArea";

let make _ => {
  ...component,
  render: fun _self =>
    <div className="App-header">
      <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      <p> (ReasonReact.stringToElement "Touch Screen or using arrow keys") </p>
    </div>
};
