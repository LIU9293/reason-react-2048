[%bs.raw {|require('./result.css')|}];

let component = ReasonReact.statelessComponent "Result";

let make ::failure ::totalScore ::highestScore ::onReplay _ => {
  ...component,
  render: fun _self =>
    if failure {
      Js.log "end !!!!!";
      <div className="end_layer">
        <div className="message">
          (
            ReasonReact.stringToElement (
              highestScore >= 2048 ? "You did it !" : "Just a little more !"
            )
          )
        </div>
        <div className="scoreArea center">
          <div className="scoreAreaInner center">
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
        <div className="to_github">
          <a
            className="github_link"
            href="https://github.com/LIU9293/reason-react-2048">
            (ReasonReact.stringToElement "Give me a star on github ~")
          </a>
        </div>
        <div className="replay">
          <button className="replay-button" onClick=onReplay>
            (ReasonReact.stringToElement "Try again")
          </button>
        </div>
      </div>
    } else {
      ReasonReact.nullElement
    }
};
