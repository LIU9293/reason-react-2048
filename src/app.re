let component = ReasonReact.statelessComponent "App";

let make ::message _children => {
  ...component,
  render: fun _self =>
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.stringToElement "ReasonReact 2048") </h2>
      </div>
      <div className="game-area">
        <Board />
      </div>
    </div>
};
