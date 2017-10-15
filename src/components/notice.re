let component = ReasonReact.statelessComponent "Notice";

let make _ => {
  ...component,
  render: fun _self =>
    <div className="notice">
      <p>
        (ReasonReact.stringToElement "Touch (mobile) / Arrow Keys (Desktop)")
      </p>
      (ReasonReact.stringToElement "Made with Reason by ")
      <a href="https://github.com/LIU9293" className="github_link">
        (ReasonReact.stringToElement "liu kai")
      </a>
    </div>
};
