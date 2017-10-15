let component = ReasonReact.statelessComponent "TitleArea";

let make ::totalScore ::highestScore _ => {
  ...component,
  render: fun _self =>
    <div className="App-header">
      <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      /* <p> (ReasonReact.stringToElement "Touch Screen or using arrow keys") </p> */
      <div className="scoreArea">
        <div className="scoreAreaInner">
          <div className="scoreLabel">
            (ReasonReact.stringToElement "Total")
          </div>
          <div className="score">
            (ReasonReact.stringToElement (string_of_int totalScore))
          </div>
        </div>
        <div className="scoreAreaInner">
          <div className="scoreLabel">
            (ReasonReact.stringToElement "Highest")
          </div>
          <div className="score">
            (ReasonReact.stringToElement (string_of_int highestScore))
          </div>
        </div>
      </div>
    </div>
};
